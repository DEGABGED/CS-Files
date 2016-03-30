#include <stdio.h>
#include <stdlib.h>

typedef struct Stacks{
	int val;
	struct Stacks * down;
} Stack;

void newStack(int val, Stack * stack){
	stack = (Stack*) malloc(sizeOf(Stack));
	stack->val = val;
	stack->down = NULL;
}

Stack * push(Stack * stack){
	printf("Input number: ");
	int val;
	if(stack == NULL){
		newStack(val, stack);
		return stack;
	}
	scanf("%d", &val);
	Stack * top = (Stack*) malloc(sizeOf(Stack));
	top->val = val;
	top->down = stack;
	return top;
}

int main(){
	Stack * stack = NULL;
	char ch;
	do{
		printf("\n(P)ush / P(o)p / Pee(k) / (V)iew / (Q)uit: ");
		ch = fgetc(stdin);
		switch(ch){
			case 'q': printf("Bye!\n"); break;
			case 'p': stack = push(stack);
			default: printf("Try again.\n"); break;
		}
	}while(ch != 'q');
	free(stack);
}
