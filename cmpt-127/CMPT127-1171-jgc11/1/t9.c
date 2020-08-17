#include <stdio.h>
#include <math.h>

int main(void) {
	float x = 0;
	float y = 0;
	float z = 0;
	int check = scanf("%f %f %f", &x, &y, &z);
	while (check != EOF) {
		int j;
		int n;
		for (j=z-1;j>=0;j--) {
			int left = floor( j * (x/(2.0*z)) );
			int right = ceil( (x-1) + -j * (x/(2.0*z)) );	
			if (j==z-1) {
				for (n=0;n<x;n++) {
					if (n < left) {
						printf(" ");
					} else if (n >= left && n <= right) {
						printf("#");
					}
				}
				printf("\n");
			}
			if (j > 0 && j < z-1) {
				for (n=0;n<x;n++) {
					if (n == left || n == right) {
						printf("#");
					} else if  (n > left && n < right) {
						printf(".");
					} else if (n < left) {
						printf(" ");
					}
				}
				printf("\n");
			}
			if (j == 1) {
				for (n=0;n<x;n++) {
					printf("#");
				}
				printf("\n");
			}	
		}
		check = scanf("%f %f %f", &x, &y, &z);
	}
}

