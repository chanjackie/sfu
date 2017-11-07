#include <stdio.h>

int main(void) {
	int i = 0;
	int check = scanf("%d", &i);
	while (1) {
		if (check == EOF) {
			break;
		}
		int n;
		for (n = 0; n<i; n++) {
			printf("#");
		}
		printf("\n");
		check = scanf("%d", &i);
	}
		
}
