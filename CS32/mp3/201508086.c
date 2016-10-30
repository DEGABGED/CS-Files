#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
	int i;
	int a_i; // Shares of a stock in the optimal portfolio
	double r_i; // Ratio of shares of a stock in any optimal portfolio
	int s_i; // Shares of a stock in the current portfolio
	int s_final; // Initial s_i value
	double mr_i; // Ratio of shares of a stock in an optimal portfolio w same no. of shares
	int k_i; // Number of shares to buy before the bounds change
	int b_i; // 1 if upper bound; 0 if lower bound; -1 if lagging behind
	struct List * next;
} List;

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

// Check if correct
void printPortfolio(List * portfolio) {
	// Check if correct reading
	List * ptr = portfolio;
	printf("Stock\ta_i\tr_i\t\ts_i\ts_final\tmr_i\t\tk_i\tb_i\n");
	while(ptr != NULL) {
		printf("%d\t%d\t%f\t%d\t%d\t%f\t%d\t%d\n",
				ptr->i, ptr->a_i, ptr->r_i, ptr->s_i, ptr->s_final,
				ptr->mr_i, ptr->k_i, ptr->b_i);
		ptr = ptr->next;
	}
}

int main() {
	FILE * fin = fopen("input.txt", "r");
	int m, A = 0, m_orig, n, s;
	char lc;
	fin = readNumber(fin, &n, &lc);
	fin = readNumber(fin, &m, &lc);
	int i = 0;
	List * portfolio = NULL;
	List * ptr = NULL;
	// Instantiate portfolio (optimal portfolio)
	for(;i<n;i++) {
		ptr = (List*) malloc(sizeof(List));
		ptr->i = i+1;
		fin = readNumber(fin, &(ptr->a_i), &lc);
		A += ptr->a_i;
		ptr->next = portfolio;
		ptr->s_i = 0;
		portfolio = ptr;
	}
	// Read file (s_i)
	for(i=0;i<m;i++) {
		fin = readNumber(fin, &s, &lc);
		ptr = portfolio;
		while(ptr != NULL) {
			if(ptr->i == s) ptr->s_i++;
			ptr = ptr->next;
		}
	}
	// Do r_i
	ptr = portfolio;
	while(ptr != NULL) {
		ptr->s_final = ptr->s_i + ptr->a_i;
		ptr->r_i = (double) ptr->a_i / A;
		ptr->mr_i = ptr->r_i * m;
		ptr->k_i = (((int) ptr->mr_i + 1) - ptr->mr_i) / ptr->r_i;
		ptr->k_i++;
		ptr->b_i = (int) ptr->mr_i;
		if(ptr->b_i == ptr->s_i) ptr->b_i = 0;
		else if(ptr->b_i == ptr->s_i - 1) ptr->b_i = 1;
		else ptr->b_i = -1;
		ptr = ptr->next;
	}

	// Actually do shit
	printPortfolio(portfolio);
	int unoptimal = 0;
	List * stockChoice = NULL;
	for(i=0; i<A; i++) {
		// Buy A shares until it reaches the optimal portfolio + initial portfolio
		// or until it breaks optimality
		stockChoice = NULL;
		m++;
		// 1: Add to the number of shares bought
		// If stockChoice is still NULL; or another needed is found, just quit
		for(ptr = portfolio; ptr != NULL; ptr = ptr->next) {
			// Update values
			if(ptr->s_i == ptr->s_final) continue;
			ptr->mr_i += ptr->r_i; // m += 1
			ptr->k_i--;
			if(ptr->k_i == 0) { // Bound change
				ptr->b_i--;
				ptr->k_i = (((int) ptr->mr_i + 1) - ptr->mr_i) / ptr->r_i;
				ptr->k_i++;
			}
			if(unoptimal == 1) continue;

			// Check if said stock is "alanganin"
			if(ptr->b_i < 0) {
				// Not buying this means unoptimality by lower bound
				if(stockChoice != NULL && stockChoice->b_i < 0) {
					unoptimal = 1; // Cannot buy this since 1 is already bought
				}
				else stockChoice = ptr;
				continue;
			}

			// Check if this is the one w the lowest k_i
			if(stockChoice != NULL) { // Compare ptr to stockChoice
				if(ptr->b_i == 0 && stockChoice >= 0 && ptr->k_i < stockChoice->k_i) {
					stockChoice = ptr;
				}
			} else { // Get stock if lower bound (you cannot buy a higher bouded stock)
				if(ptr->b_i == 0) stockChoice = ptr;
			}
		}

		// 2. Buy a share from the chosen stock
		if(stockChoice == NULL) {
			printf("null\n");
			break;
		}
		stockChoice->s_i++;
		stockChoice->b_i++;
		if(unoptimal == 1) {
			printf("unopt\n");
			break;
		}
		//printf("\n");
		//printPortfolio(portfolio);
	}
	printf("%d\n", i == A ? -1 : i);
}
