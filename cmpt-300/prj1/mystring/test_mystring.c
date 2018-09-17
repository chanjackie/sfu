#include "mystring.h"
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The following are simple tests to help you.
 * You should develop more extensive tests to try and find bugs.
 */
int main()
{
	const int SIZE = 100;
	char buffer[SIZE];
	char buffer2[SIZE];
	char buffer3[SIZE];

	assert(mystrlen("cmpt 300") == 8);
	assert(mystrlen("") == 0);	
	assert(mystrlen("  ayy ") == 6);
	printf("Passed mystrlen\n");

	char tester[SIZE];
	mystrcpy(buffer, "I am testing my string functions!");
	assert(strcmp(buffer, "I am testing my string functions!") == 0);
	mystrcpy(buffer2, "");
	assert(strcmp(buffer2, "") == 0);
	mystrcpy(buffer3, " hello 123");
	assert(strcmp(buffer3, " hello 123") == 0);
	assert(strcmp(buffer3, " hello 12") > 0);
	mystrcpy(tester, "  ");
	assert(strcmp(tester, "  ") == 0);
	printf("Passed mystrcpy\n");

	assert(mystrcmp ("I love coding", "I love coding") == 0);
	assert(mystrcmp ("I love codin", "I love coding") == -1);
	assert(mystrcmp ("I love coding", "I love codin") == 1);
	assert(mystrcmp ("", "") == 0);
	assert(mystrcmp ("abcd", "efgh") == -1);
	assert(mystrcmp ("efgh", "abcd") == 1);
	printf("Passed mystrcmp\n");

	char *dupStr = mystrdup(buffer);
	assert (!strcmp(buffer, dupStr));
	assert (buffer != dupStr);
	char *dupStr2 = mystrdup(buffer2);
	assert (!strcmp(buffer2, dupStr2));
	assert (buffer2 != dupStr2);
	char *dupStr3 = mystrdup(buffer3);
	assert (!strcmp(buffer3, dupStr3));
	assert (buffer3 != dupStr3);

	if (dupStr != NULL)
		free (dupStr);
	if (dupStr2 != NULL)
		free (dupStr2);
	if (dupStr3 != NULL)
		free (dupStr3);

	printf ("\nPassed VERY simple tests, remember to develop more tests.\n");

	return 0;
}

