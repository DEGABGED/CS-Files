#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Threaded binary tree with inorder traversal and tree head
typedef struct Stock {
	int i;
	int a_i; // Shares of a stock in the optimal portfolio
	double r_i; // Ratio of shares of a stock in any optimal portfolio
	int s_i; // Shares of a stock in the current portfolio
	int s_final; // Final s value allotted
	int k_i; // Number of shares to buy before the bounds change
	int b_i; // s_i - s_i_lowerbound
	// mr_i, k_i, b_i can be computed on hand
	int ltag;
	int rtag;
	struct Stock * left;
	struct Stock * right;
} Stock;

Stock * insuc(Stock * ptr) {
	Stock * output = ptr->right;
	if(ptr->rtag == 1) {
		while(output->ltag == 1) { output = output->left; }
	}
	return output;
}

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
void printPortfolio(Stock * portfolio) {
	// Check if correct reading
	Stock * ptr = portfolio;
	printf("Stock\ta_i\tr_i\t\ts_i\ts_final\tk_i\tb_i\n");
	while(1) {
		// Inorder traversal
		ptr = insuc(ptr);
		if(ptr == portfolio) return;
		printf("%d\t%d\t%f\t%d\t%d\t%f\t%d\t%d\n",
				ptr->i, ptr->a_i, ptr->r_i, ptr->s_i,
				ptr->s_final, ptr->k_i, ptr->b_i);
	}
}
