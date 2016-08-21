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

Stack * pop(Stack * top, int * num) {
	if (top == NULL) {
		*num = -1;
		return NULL;
	} else {
		*num = top->data;
		Stack * retnode = top;
		top = top->below;
		free(retnode);
		return top;
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

// Tries to get xperm using a stack and x from {1..N}
// Returns the stack, and sets the new x and is_sp
Stack * validSoFar(Stack * top, int * x, int xperm, int N, int * is_sp) {
	int dump = 0;
	if(top != NULL && xperm < top->data) {
		*is_sp = 0;
	} else {
		while(top == NULL || top->data != xperm) {
			if(*x > N || (top != NULL && xperm < top->data)) {
				*is_sp = 0;
				return top; //break;
			}
			top = push(top, *x);
			(*x)++;
		}
		top = pop(top, &dump);
	}
	//printf("top:%d, x:%d, xperm:%d, issp:%d\n", top == NULL ? -1 : top->data, *x, xperm, *is_sp);
	return top;
}

Stack * freeStack(Stack * top) {
	int dump = 0;
	while(top != NULL) top = pop(top, &dump);
	return NULL;
}

void main() {
	// FILE IO
	char lastchar = ' ';
	int numinput;
	int stack_size = -1;
	Stack * top = NULL;
	int numptr = 0;
	FILE * fin;
	FILE * fout;
	int not_end = 1;
	int is_sp = 1;
	fin = fopen("mp1.txt", "r");
	fout = fopen("201508086.txt", "w");

	// Program loop (once per test case)
	while(!feof(fin) && not_end) {
		if(top != NULL) top = freeStack(top);
		fin = readNumber(fin, &numinput, &lastchar);
		is_sp = 1;
		if(lastchar == ':') {
			// Number is size of stack
			if(stack_size >= 0) fputs("\n", fout);

			// Init stack and list 1 to N
			stack_size = numinput;
			numptr = 1;

			// List reading loop (once per stack element)
			// Exits when is_sp is false, when numptr exceeds stacksize, or when the last element is reached
			while(is_sp && numptr <= stack_size+1 && lastchar != '\n') {
				fin = readNumber(fin, &numinput, &lastchar);
				if(lastchar == ',' || lastchar == '\n') {
					top = validSoFar(top, &numptr, numinput, stack_size, &is_sp);
				}
			}

			if(is_sp) fputs("YES", fout);
			else fputs("NO", fout);
		} else if(lastchar == 'E'){
			// It's probably the end
			not_end = 0;
		}
	}

	// Ending
	fclose(fin);
}
