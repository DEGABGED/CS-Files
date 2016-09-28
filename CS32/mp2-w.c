#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILLER_SIZE 50

typedef struct List {
	int data;
	struct List * next;
} List;

List * add(List * a, List * b) {
	// Assume both numbers are positive or both are negative
	// Find absolute value of sum
	int k = a->data;
	if(b->data > a->data) k = b->data;
	k++;
	int c = 0; // Initialize c(-1) to 0
	int r = 10; // Base 10 integers
	int i = 0; // Iterator

	for(; i < k-2; i++) {
		
	}
}

List * mult(List * a, List * b) {

}

List * sub(List * a, List * b) {

}

List * base10to27(List * a) {

}

List * base27to10(List * a) {

}

List * init() {
	List * out = (List*) malloc(sizeof(List));
	out->data = 0; // Size of the list
	out->next = NULL;
	return out;
}

// Append puts the new digit between the list head and first digit
List * append(List * list, int data) {
	List * newnode = (List*) malloc(sizeof(List));
	newnode->data = data;
	newnode->next = list->next;
	list->next = newnode;
	list->data = list->data + 1;
	return list;
}

List * freeList(List * list) {
	List * ptr = list;
	while(ptr != NULL) {
		list = list->next;
		free(ptr);
		ptr = list;
	}
	return NULL;
}

FILE * readFiller(FILE * fin, char * str) {
	int ndx = 0;
	str[ndx] = (char) fgetc(fin);
	ndx++;
	while(str[ndx] != ':' && str[ndx] != '\n' && ndx < FILLER_SIZE) {
		str[ndx] = (char) fgetc(fin);
		if(str[ndx] == ':') {
			ndx++;
			str[ndx] = (char) fgetc(fin);
			ndx++;
			break;
		} else if(str[ndx] == '\n') {
			ndx++;
			break;
		}
		ndx++;
	}
	if(ndx < FILLER_SIZE) str[ndx] = '\0'; //Terminate the input string
	else str[49] = '\0';
	return fin;
}

FILE * readNumber(FILE * fin, List * list) {
	// Declarations
	char stream = '$';
	int numstream = -1;
	while(stream != ',' && stream != '\n') {
		stream = (char) fgetc(fin);
		//if(stream == ' ') continue;
		numstream = atoi(&stream);
		if(numstream == 0 && stream != '0') continue;

		// Append number to list
		list = append(list, numstream);
	}
	return fin;
}

void printNumber(List * num) {
	// In reverse
	List * ptr = num->next;
	while(ptr != NULL) {
		printf("%d", ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
	return;
}

void main() {
	// Declarations
	FILE * fin;
	FILE * fout;
	fin = fopen("INPUT.txt", "r");
	fout = fopen("201508086.txt", "w");

	char filler[FILLER_SIZE]; //Stores the useless text (eg. Alice / Bob / etc.)
	filler[0] = 'Z';
	List * p = init();
	List * q = init();
	List * e = init();
	List * m = init();
	
	while(filler[0] != 'E') {
		fin = readFiller(fin, filler);
		printf("/%s\\\n", filler);
		if(filler[0] == 'C') {
			//Case input
			// Reset p,q,e
			p = freeList(p);
			q = freeList(q);
			e = freeList(e);
			p = init();
			q = init();
			e = init();

			// Parse p,q,e
			fin = readNumber(fin, p);
			fin = readNumber(fin, q);
			fin = readNumber(fin, e);

			//Check if tama pagkabasa
			printNumber(p);
			printNumber(q);
			printNumber(e);
			printf("/%s\\\n", filler);
		} else if(filler[0] == 'B') {
			// Decrypt m
			printf("Decrypt X\n");
		} else if(filler[0] == 'A') {
			// Encrypt m
			printf("Encrypt M\n");
		} else if(filler[0] == 'E') {
			// END
		}
		if(feof(fin)) break;
	}

	printf("end/%s\\\n", filler);
	// Ending
	fclose(fin);
	fclose(fout);
}
