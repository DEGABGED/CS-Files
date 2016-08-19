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

int stackPerm(Stack * top, int size) {

}

Stack * freeStack(Stack * top) {
	int dump = 0;
	while(top != NULL) pop(top, &dump);
	return NULL;
}

void main() {
	// FILE IO
	char lastchar;
	int numinput;
	int stack_size = 0;
	Stack * top = NULL;
	Stack * ptr = NULL;
	int * numlist = NULL;
	int numptr = 0;
	FILE * fin;
	int not_end = 1;
	int is_sp = 1;
	fin = fopen("input.txt", "r");

	while(!feof(fin) && not_end) {
		fin = readNumber(fin, &numinput, &lastchar);
		switch(lastchar) {
			case ':':
				// Number is size of stack
				stack_size = numinput;
				numlist = (int*) malloc(sizeof(int) * stack_size);
				while(numptr < stack_size) {
					numlist[numptr] = numptr + 1;
					numptr++;
				}
				numptr = 0;
				is_sp = 1;
				break;
			case ',':
				// Number is part of stack
				if(top != NULL && numinput < top->data) {
					is_sp = 0;
					break;
				} else {
					do {
						top = push(top, numlist[numptr]);
						numptr++;
					} while(top != NULL && top->data != numinput);
					top = pop(top, &numinput);
				break;
				}
			case '\n':
				// Stack is finished
				if(numinput == top->data && is_sp) printf("YES\n");
				else printf("NO\n");
				freeStack(top);
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
