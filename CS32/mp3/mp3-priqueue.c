#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sequential Heap
typedef struct Stock {
	int i;
	int a_i; // Shares of a stock in the optimal portfolio
	double r_i; // Ratio of shares of a stock in any optimal portfolio
	int s_i; // Shares of a stock in the current portfolio
	int s_final; // Final s value allotted
	// mr_i, k_i, b_i can be computed on hand
	int m;
	double mr_i;
	int k_i; // Number of shares to buy before the bounds change
	int b_i; // s_i - s_i_lowerbound
} Stock;

FILE * readNumber(FILE * fin, int * number, char * lastchar) {
	char input;
	int parsed_input = 0;
	int final_input = 0;
	input = (char) fgetc(fin);
	parsed_input = atoi(&input);
	while(parsed_input != 0 || input == '0') {
		final_input = final_input*10 + parsed_input;
		input = (char) fgetc(fin);
		parsed_input = atoi(&input);
	}
	*number = final_input;
	*lastchar = input;
	return fin;
}

void printPortfolio(Stock * pf, int n) {
	int ndx = 0;
	printf("Stock\ta_i\tr_i\t\ts_i\ts_final\tmr_i\t\tk_i\tb_i\n");
	for(ndx=0;ndx<n;ndx++) {
		printf("%d\t%d\t%f\t%d\t%d\t%f\t%d\t%d\t%d\n",
				pf[ndx].i, pf[ndx].a_i, pf[ndx].r_i,
				pf[ndx].s_i, pf[ndx].s_final, pf[ndx].mr_i,
				pf[ndx].k_i, pf[ndx].b_i, pf[ndx].m);
	}
	printf("\n");
}

void printPortfolioCorrect(Stock * pf, int n) {
	int ndx = 0, i = 0;
	printf("Stock\ta_i\tr_i\t\ts_i\ts_final\tmr_i\t\tk_i\tb_i\n");
	for(i=1;i<=n;i++) {
		for(ndx=0;ndx<n;ndx++) {
			if(pf[ndx].i == i) {
				printf("%d\t%d\t%f\t%d\t%d\t%f\t%d\t%d\t%d\n",
						pf[ndx].i, pf[ndx].a_i, pf[ndx].r_i,
						pf[ndx].s_i, pf[ndx].s_final, pf[ndx].mr_i,
						pf[ndx].k_i, pf[ndx].b_i, pf[ndx].m);
				break;
			}
		}
	}
	printf("\n");
}

int compare(Stock a, Stock b) {
	// Returns -1 if Stock a is of higher priority, 1 otherwise
	// Stock a should be the top of the minheap to reduce amounts of
	//     switching when a = b in priority
	// Assume values are precomputed
	// 1. Check for the one more behind
	//if(a.b_i != b.b_i) return a.b_i < b.b_i ? -1 : 1;
	if(a.b_i < 0) return -1; // A dead fish floats
	if(b.b_i < 0) return 1;
	// 2. Check for the one with the lower k_i
	if(a.k_i < 0) return 1; // A large enough value overflows
	if(b.k_i < 0) return -1;
	if(a.k_i == b.k_i) return 0;
	return a.k_i < b.k_i ? -1 : 1;
}

void updateVars(Stock * ptr, int m) {
	ptr->m = m;
	ptr->mr_i = ptr->r_i * m;
	ptr->k_i = ((ptr->s_i + 1) - ptr->mr_i) / ptr->r_i;
	ptr->k_i++;
	ptr->b_i = (int) ptr->mr_i;
	if(ptr->b_i == ptr->s_i) ptr->b_i = 0;
	else if(ptr->b_i == ptr->s_i - 1) ptr->b_i = 1;
	else ptr->b_i = -1;
}

void heapify(Stock * pf, int r, int n, int m) {
	// 1-INDEXED
	updateVars(&(pf[r-1]), m);
	Stock k = pf[r-1];
	int i = r, j = 2*i, c_jj, c_jk;
	while(j <= n) {
		updateVars(&(pf[j-1]), m);
		if(j < n) {
			updateVars(&(pf[j]), m);
			c_jj = compare(pf[j], pf[j-1]);
			if(c_jj < 0) j++;
		}
		if(compare(pf[j-1], k) < 0) {
			pf[i-1] = pf[j-1];
			i = j;
			j = 2*i;
		} else { break; }
	}
	pf[i-1] = k;
}

void main() {
	FILE * fin = fopen("case.txt", "r");
	FILE * fout = fopen("out.txt", "w");
	int m = 0, A = 0, m_orig = 0, n = 0, s = 0, i = 0;
	// n: number of stocks; m: number of shares
	char lc;
	Stock * pf = NULL;
	while(1) {
		fin = readNumber(fin, &n, &lc);
		fin = readNumber(fin, &m, &lc);
		if(n == 0) break;
		m_orig = m;
		//printf("n: %d, m: %d\n", n, m);
		A = 0;

		// Construct the array
		pf = (Stock*) malloc(sizeof(Stock) * n);
		// Read optimal portfolio
		for(i=0;i<n;i++) {
			pf[i].i = i+1;
			fin = readNumber(fin, &(pf[i].a_i), &lc);
			A += pf[i].a_i;
			pf[i].s_i = 0;
		}
		// Read file (s_i)
		for(i=0;i<m;i++) {
			fin = readNumber(fin, &s, &lc);
			pf[s-1].s_i++;
		}
		// Compute r_i and other values
		for(i=0;i<n;i++) {
			pf[i].s_final = pf[i].s_i + pf[i].a_i;
			pf[i].r_i = (double) pf[i].a_i / A;
			pf[i].mr_i = pf[i].r_i * m;
			pf[i].m = m;
			pf[i].k_i = ((pf[i].s_i + 1) - pf[i].mr_i) / pf[i].r_i;
			pf[i].k_i++; // ???
			pf[i].b_i = (int) pf[i].mr_i;
			if(pf[i].b_i == pf[i].s_i) pf[i].b_i = 0;
			else if(pf[i].b_i == pf[i].s_i - 1) pf[i].b_i = 1;
			else pf[i].b_i = -1;
		}

		// Convert sequential thing to heap (O(n log n) ?)
		int r = n / 2;
		for(;r>0;r--) { heapify(pf, r, n, m); }
		// Actually do shit
		//printPortfolioCorrect(pf, n);

		// So I guess heapifying works for now?
		//printf("Real loop:\n");
		updateVars(&(pf[0]), m); // Just in case
		m++;
		for(;m<A+m_orig+1;m++) {
			// Check if next in line is an upper bound or is left for dead
			i=0; // alt top
			if(pf[0].b_i == 1) {
				// Search all and check if all are 1
				for(i=1;i<n;i++) {
					updateVars(&(pf[i]), m);
					if(pf[i].b_i != 1) break;
				}
				if(i == n) break;
				//printf("i = %d\n", i);
			}
			if(pf[i].b_i != 0) break;
			pf[i].s_i++; // Buy a share
			updateVars(&(pf[i]), m);
			// Get the next in line
			heapify(pf, 1, n, m);
			updateVars(&(pf[0]), m); // Just in case
			if(m==239 || m==238) {
				printf("m=%d\n", m);
				printPortfolio(pf, n);
			}
			//printf("\n");
		}
		//printf("%d\n", m >= A + m_orig ? -1 : m-m_orig-2);
		printPortfolioCorrect(pf,n);
		if(m >= A + m_orig) {
			fprintf(fout, "NO LIMIT\n");
		} else {
			fprintf(fout, "%d\n", m-m_orig-2 < 0 ? 0 : m-m_orig-2);
		}
		free(pf);
	}

	// End
	fclose(fin);
	fclose(fout);
}
