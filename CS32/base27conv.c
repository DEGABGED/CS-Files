#include <stdio.h>

int main() {
	int x = -4;
	int i = -4;

	int absx = x;
	int absi = i;

	if(absx < 0) absx *= -1;
	if(absi < 0) absi *= -1;

	if((absx != x) ^ (absi != i)) printf("neg\n");
	else printf("pos\n");
}
