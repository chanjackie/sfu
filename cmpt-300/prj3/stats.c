#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "stats.h"

typedef struct {
	int num_made;
	int num_eaten;
	double min_delay;
	double avg_delay;
	double max_delay;
} stats_t;

stats_t *statsArray;

void stats_init(int num_producers) {
	statsArray = malloc(sizeof(stats_t)*num_producers);
	for (int i=0;i<num_producers;i++) {
		statsArray[i].num_made = 0;
		statsArray[i].num_eaten = 0;
		statsArray[i].min_delay = -1;
		statsArray[i].avg_delay = -1;
		statsArray[i].max_delay = -1;
	}
	return;
}

void stats_cleanup(void) {
	free(statsArray);
	return;
}

void stats_record_produced(int factory_number) {
	statsArray[factory_number].num_made++;
	return;
}

void stats_record_consumed(int factory_number, double delay_in_ms) {
	statsArray[factory_number].num_eaten++;
	if (statsArray[factory_number].min_delay == -1) {
		statsArray[factory_number].min_delay = delay_in_ms;
		statsArray[factory_number].max_delay = delay_in_ms;
		statsArray[factory_number].avg_delay = delay_in_ms;
	} else {
		if (delay_in_ms < statsArray[factory_number].min_delay) {
			statsArray[factory_number].min_delay = delay_in_ms;
		}
		if (delay_in_ms > statsArray[factory_number].max_delay) {
			statsArray[factory_number].max_delay = delay_in_ms;
		}
		statsArray[factory_number].avg_delay = statsArray[factory_number].avg_delay
		 + (delay_in_ms - statsArray[factory_number].avg_delay)/statsArray[factory_number].num_eaten;
	}
	return;
}

void stats_display(int num_producers) {
	printf("Statistics: \n");
	printf("%8s%8s%8s%16s%16s%16s\n", "Factory#", "Made", "Eaten", "Min Delay[ms]", "Avg Delay[ms]", "Max Delay[ms]");
	for (int i=0;i<num_producers;i++) {		
		printf("%8d%8d%8d%16.5f%16.5f%16.5f\n", i, statsArray[i].num_made, statsArray[i].num_eaten, 
			statsArray[i].min_delay, statsArray[i].avg_delay, statsArray[i].max_delay);
		if (statsArray[i].num_eaten != statsArray[i].num_made) {
			printf("ERROR: Mismatch between number made and eaten\n");
		}
	}
	return;
}