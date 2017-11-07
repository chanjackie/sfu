#include <stdio.h>
#include <string.h>

int main() {
	char letter[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	float freq[26] = {0};
	float totalletters = 0;
	char k;
	int i;
	while((k = getchar()) != EOF) {
		if (isalpha(k)) {
			totalletters++;
			for (i=0;i<26;i++) {
				if (k == letter[i] || k == toupper(letter[i])) {
					freq[i]++;
				}
			}
		}
	}
	for (i=0;i<26;i++) {
		freq[i] = freq[i]/totalletters;
	}
	for (i=0;i<26;i++) {
		if (freq[i] != 0) {
			printf("%c %.4f\n", letter[i], freq[i]); 
		}
	}
}
