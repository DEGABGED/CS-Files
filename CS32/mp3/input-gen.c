#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE * fout = fopen("gen-input.txt", "w");
	srand(time(NULL));
	int cases = 100; // Dev-defined
	int i = 0, m = 0, n = 0, mi, ni, out;
	for(i=0; i<cases; i++) {
		n = rand() % 1000; // Dev-defined
		m = rand() % 100; // Dev-defined
		fprintf(fout, "%d %d\n", n, m);
		for(ni=0; ni<n; ni++) { // Optimal portfolio
			out = rand() % 100; // Dev-defined
			fprintf(fout, "%d%c", out, ni < n-1 ? ' ' : '\n');
		}
		for(mi=0; mi<m; mi++) { // Shares bought
			fprintf(fout, "%d%c", mi+1, mi < m-1 ? ' ' : '\n');
		}
	}
	fclose(fout);
}
