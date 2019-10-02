#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "bbuff.h"
#include "stats.h"

// write(STDOUT_FILENO, "\n", strlen("\n"));
_Bool stop_thread = false;

typedef struct  {
    int factory_number;
    double time_stamp_in_ms;
} candy_t;

double current_time_in_ms(void) {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}

void *candyFactory(void *factoryNum) {
	int thisNum = *((int *)factoryNum);
	while(!stop_thread) {
		int waitTime = rand() % 4;
		printf("This is factory number %d and will wait %ds\n", thisNum, waitTime);
		candy_t *candy = malloc(sizeof(candy_t));
		candy->factory_number = thisNum;
		candy->time_stamp_in_ms = current_time_in_ms();
		bbuff_blocking_insert(candy);
		stats_record_produced(thisNum);
		sleep(waitTime);
	}
	printf("Candy-factory %d done\n", thisNum);
	free(factoryNum);
	return NULL;
}

void *kid() {
	while(1) {
		candy_t *candy = bbuff_blocking_extract();
		double delay = current_time_in_ms() - candy->time_stamp_in_ms;
		stats_record_consumed(candy->factory_number, delay);
		free(candy);
		sleep(rand()%2);
	}
}

int main(int argc, char* argv[]) {
	// Extract arguments
	if (argc != 4) {
		write(STDOUT_FILENO, "Incorrect number of arguments.\n", strlen("Incorrect number of arguments.\n"));
		return -1;
	}
	int *args = malloc(sizeof(int)*3);
	for (int i=1;i<4;i++) {
		args[i-1] = atoi(argv[i]);
		if (args[i-1] <= 0) {
			write(STDOUT_FILENO, "Arguments must be greater than 0.\n", strlen("Arguments must be greater than 0.\n"));
			return -1;
		}
	}

	// Initialize modules
	bbuff_init();
	stats_init(args[0]);
	pthread_t *factoryThreadNums = malloc(sizeof(pthread_t)*args[0]);
	pthread_t *kidThreadNums = malloc(sizeof(pthread_t)*args[1]);

	// Launch factory threads
	for (int i=0;i<args[0];i++) {
		pthread_t factoryThreadId;
		int *factoryNum = malloc(sizeof(*factoryNum));
		*factoryNum = i;
		if (pthread_create(&factoryThreadId, NULL, candyFactory, factoryNum)) {
			printf("Error creating factory thread.\n");
			return -1;
		}
		factoryThreadNums[i] = factoryThreadId;
	}

	// Launch kid threads
	for (int i=0;i<args[1];i++) {
		pthread_t kidThreadId;
		if (pthread_create(&kidThreadId, NULL, kid, NULL)) {
			printf("Error creating kid thread.\n");
			return -1;
		}
		kidThreadNums[i] = kidThreadId;
	}

	// Wait for requested time
	for (int i=0;i<args[2];i++) {
		sleep(1);
		printf("Time %ds\n", i+1);
	}

	// Stop factory threads
	stop_thread = true;
	for (int i=0;i<args[0];i++) {
		pthread_join(factoryThreadNums[i], NULL);
	}

	// Wait until no more candy
	while (!bbuff_is_empty()) {
		printf("Buffer status: %s\n", bbuff_is_empty() ? "Empty" : "Not Empty");
		sleep(1);
	}	
	printf("Buffer empty, now stopping kids...\n");

	// Stop kid threads
	for (int i=0;i<args[1];i++) {
		pthread_cancel(kidThreadNums[i]);
		pthread_join(kidThreadNums[i], NULL);
	}

	// Print statistics
	stats_display(args[0]);

	// Cleanup allocated memory
	free(factoryThreadNums);
	free(kidThreadNums);
	free(args);
	stats_cleanup();


	return 0;
}

