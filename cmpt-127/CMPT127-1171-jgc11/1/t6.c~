#include <stdio.h>
#include <math.h>

int main(void) {
	float i = 0;
	int check = scanf("%f", &i);
	float small = i;
	float large = i;
	float mean = i;
	float sum = 0;
	float entries = 0;
	while (1) {
		if (check == EOF) {
			printf("%.2f %.2f %.2f\n", small, large, mean);
			break;
		}
		if (i < small) {
			small = i;
		}
		if (i > large) {
			large = i;
		}
		sum = sum + i;
		entries++;
		mean = sum/entries;
		check = scanf("%f", &i);
	}
}
