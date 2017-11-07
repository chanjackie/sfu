#include <stdio.h>

int main(void)
{
	int a = sizeof(char) * 8;
	int b = sizeof(unsigned char) * 8;
	int c = sizeof(int) * 8;
	int d = sizeof(unsigned int) * 8;
	int e = sizeof(long) * 8;
	int f = sizeof(unsigned long) * 8;
	int g = sizeof(float) * 8;
	int h = sizeof(double) * 8;
	int i = sizeof(long double) * 8;
	printf("%d %d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h ,i);
	return 0;
}
