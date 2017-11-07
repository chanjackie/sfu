#include <stdio.h>
#include <string.h>

int main( int argc, char* argv[]) {
	int alen = strlen(argv[1]);
	int blen = strlen(argv[2]);
	char astr[alen];
	char bstr[blen];
	strcpy (astr, argv[1]);
	strcpy (bstr, argv[2]);
	int k;
	int flag;
	for (k=0;k<blen;k++) {
		int l;
		flag = 0;
		for (l=0;l<alen;l++) {
			if (bstr[k] == astr[l]) {
				flag = 1;
			}
		}
		if (!flag) {
			printf("false\n");
			break;
		}
	}
	if (flag) {
		printf("true\n");
	}
}
