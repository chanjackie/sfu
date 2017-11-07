
#include <stdio.h>

long dot(long *, long *);

long x[2] = {5, 12};
long y[2] = {18, -4};

void main () {
	printf("The dot product of (%ld,%ld) and (%ld,%ld) is %ld.\n", x[0], x[1], y[0], y[1], dot(x,y));
	return;
}
