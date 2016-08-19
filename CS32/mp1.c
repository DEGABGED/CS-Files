#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
	int data;
	struct Stack * below;
} Stack;

Stack * push(Stack * top, int data) {
	Stack * new_top = (Stack*) malloc(sizeof(Stack));
	new_top->data = data;
	new_top->below = top;
	return new_top;
}

int pop(Stack * top) {
	if (top == NULL) return -1;
	else {
		int ret = top->data;
		Stack * retnode = top;
		top = top->below;
		free(retnode);
		return ret;
	}
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

void main() {
	// FILE IO
	/* char * input;
	int input_size = 100;
	input = (char*) malloc(input_size);
	*(input+input_size-1) = '\0';
	*/
	char lastchar;
	int numinput;
	int numlist_size = 0;
	int * numlist;
	int ptr;
	FILE * fin;
	int not_end = 1;
	fin = fopen("input.txt", "r");

	while(!feof(fin) && not_end) {
		fin = readNumber(fin, &numinput, &lastchar);
		switch(lastchar) {
			case ':':
				// Number is size of stack
				numlist_size = numinput;
				numlist = (int*) malloc(sizeof(int) * numlist_size);
				ptr = 0;
				break;
			case ',':
				// Number is part of stack
				if(ptr >= numlist_size) break;
				numlist[ptr] = numinput;
				ptr++;
				break;
			case '\n':
				// Stack is finished
				if(ptr < numlist_size)
					numlist[ptr] = numinput;
				ptr = 0;
				while(ptr < numlist_size) {
					printf("%d, ", numlist[ptr]);
					ptr++;
				}
				printf("\n\n");
				free(numlist);
				break;
			case 'E':
				// Get out
				not_end = 0;
				break;
		}
	}

	// Do stuff

	// Ending
	fclose(fin);
}
