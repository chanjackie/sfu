#include <stdio.h>

int main(void) {
	int x = 0;
	int y = 0;
	int z = 0;
	int check = scanf("%d %d %d", &x, &y, &z);
	while (1) {
		if (check == EOF) {
			break;
		}
		int n;
		for (n = 0; n<x; n++) {
			printf("#");
		}
		printf("\n");
		for (n = 0; n<(y-2); n++) {
			printf("#");
			int k;
			for (k = 0; k<(x-2); k++) {
				printf(".");
			}
			printf("#\n");
		}
		if (y > 1) {
			for (n = 0; n<x; n++) {
				printf("#");
			}		
			printf("\n");
		}
		check = scanf("%d %d %d", &x, &y, &z);
	}
	return 0;
}

