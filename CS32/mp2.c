#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILLER_SIZE 50

typedef struct List {
	int data;
	struct List * next;
} List;

List * add(List * a, List * b) {

}

List * mult(List * a, List * b) {

}

List * sub(List * a, List * b) {

}

List * init() {
	List * out = (List*) malloc(sizeof(List));
	out->data = 0; // Size of the list
	out->next = NULL;
	return out;
}

// Takes tail instead to make appending O(1)
List * append(List * list, List * tail, int data) {
	List * newnode = (List*) malloc(sizeof(List));
	newnode->data = data;
	newnode->next = NULL;
	tail->next = newnode;
	tail = newnode;

	//Update size of list
	list->data = list->data + 1;
	return tail;
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
	while(ndx < FILLER_SIZE) {
		ndx++;
		str[ndx] = (char) fgetc(fin);
		if(str[ndx] == ':') {
			ndx++;
			str[ndx] = (char) fgetc(fin);
			break;
		} else if(str[ndx] == '\n') {
			break;
		}
	}
	if(ndx < FILLER_SIZE) str[ndx] = '\0'; //Terminate the input string
	else str[49] = '\0';
	return fin;
}

FILE * readNumber(FILE * fin, List * list) {
	// Declarations
	char stream = '$';
	int numstream = -1;
	// Since list should be empty upon reading, assume list size = 0
	List * tail = list;
	while(stream != ',' && stream != '\n') {
		stream = (char) fgetc(fin);
		//if(stream == ' ') continue;
		numstream = atoi(&stream);
		if(numstream == 0 && stream != '0') continue;

		// Append number to list
		tail = append(list, tail, numstream);
	}
	return fin;
}

FILE * readMessage(FILE * fin, List * list) {
	// Declarations
	int stream = -1;
	List * tail = list;
	List * pretail = tail;
	stream = fgetc(fin);
	while(stream != 116 && stream != 10 && stream != 102) { //116: t; 10: \n
		if(stream > 64 && stream < 91) {
			stream -= 65;
		} else if(stream == 32) {
			// space
			stream = 26;
		}
		tail = append(list, tail, stream);
		if(pretail->next != NULL && pretail->next != tail) pretail = pretail->next;
		stream = fgetc(fin);
	}

	//Remove trailing whitespace
	if(tail->data == 26) {
		pretail->next = NULL;
		free(tail);
		tail = pretail;
		list->data -= 1;
	}
	return fin;
}

void printNumber(List * num) {
	// In reverse
	printf("%d::", num->data);
	List * ptr = num->next;
	while(ptr != NULL) {
		printf("%d", ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
	return;
}

void printMessage(List * msg) {
	printf("%d::", msg->data);
	List * ptr = msg->next;
	char stream = '%';
	while(ptr != NULL) {
		if(ptr->data < 10) {
			printf("%d", ptr->data);
		} else {
			if(ptr->data == 32) stream = ' ';
			else stream = (char) (ptr->data + 55);
			printf("%c", stream);
		}
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
		//printf("/%s\\\n", filler);
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
			printf("/%s\\\n", filler);
			printNumber(p);
			printNumber(q);
			printNumber(e);
		} else if(filler[0] == 'B') {
			// Decrypt m
			printf("Decrypt X\n");
			// Get X
			m = freeList(m);
			m = init();
			fin = readMessage(fin, m);
			printMessage(m);
		} else if(filler[0] == 'A') {
			// Encrypt m
			printf("Encrypt M\n");
			// Get M
			m = freeList(m);
			m = init();
			fin = readMessage(fin, m);
			printMessage(m);
		} else if(filler[0] == 'E') {
			// END
		}
		if(feof(fin)) break;
	}

	//printf("end/%s\\\n", filler);
	// Ending
	p = freeList(p);
	q = freeList(q);
	e = freeList(e);
	m = freeList(m);
	fclose(fin);
	fclose(fout);
}
