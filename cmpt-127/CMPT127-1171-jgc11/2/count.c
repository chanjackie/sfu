#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
	unsigned long int charcount = 0;
	unsigned long int wordcount = 0;
	unsigned long int linecount = 0;
	char k;
	int recentword = 0;
	while((k = getchar()) != EOF) {
		charcount++;
		if (k == '\'' || isalpha(k)) {
			recentword = 1;
		}
		if (k != '\'' && !isalpha(k) && recentword) {
			wordcount++;
			recentword = 0;
		}
		if (k == '\n') {
			linecount++;
		}
	}
	printf( "%lu %lu %lu\n", charcount, wordcount, linecount);
}
