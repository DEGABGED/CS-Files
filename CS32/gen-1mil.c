#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
	FILE * fout = fopen("mp1-vlarge.txt", "w+");
	int nmax = 10000000;
	int n = 1;
	fprintf(fout, "%d:", nmax);
	while(n <= nmax) {
		fprintf(fout, "%d", n);
		n++;
		if(n <= nmax) fputs(", ", fout);
	}
	fputs("\nEND", fout);
	fclose(fout);
}
