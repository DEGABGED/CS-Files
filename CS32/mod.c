#include <stdio.h>

int main() {
	int x = -15 % 7;
	int y = -15 / 7;
	int z = 999999;
	int z2 = 999999999;
	z2 *= 2;
	z2 += 2;
	printf("%d\n", x);
	printf("%d\n", y);
	printf("%d\n", z);
	printf("%d\n", z2);
}
