#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILLER_SIZE 50

typedef struct List {
	int data;
	struct List * next;
} List;

List * init() {
	List * out = (List*) malloc(sizeof(List));
	out->data = 0; // Size of the list
	out->next = NULL;
	return out;
}

// Prepend puts the new digit between the list head and first digit
// Use when reading from highest to lowest place value
List * prepend(List * list, int data) {
	List * newnode = (List*) malloc(sizeof(List));
	newnode->data = data;
	newnode->next = list->next;
	list->next = newnode;

	//Update size of list
	list->data = list->data + 1;
	return list;
}

// Append puts the new digit at the end
// Use when reading from lowest to highest place value
// O(1)
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

// O(e), e = number of digits of n
List * intToList(int n) {
	// Assume representation in base 10
	List * output = init();
	List * outputtail = output;
	int b = 10; //For generality
	int mod = 0;
	while(n > 0) {
		mod = n % b; // Ones digit
		outputtail = append(output, outputtail, mod);
		n = n / b; // Remainder
	}
	return output;
}

// O(n)
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
	while(stream != ',' && stream != '\n') {
		stream = (char) fgetc(fin);
		//if(stream == ' ') continue;
		numstream = atoi(&stream);
		if(numstream == 0 && stream != '0') continue;

		// Append number to list
		list = prepend(list, numstream);
	}
	return fin;
}

FILE * readMessage(FILE * fin, List * list) {
	// Declarations
	int stream = -1;
	stream = fgetc(fin);
	while(stream != 116 && stream != 10 && stream != 102) { //116: t; 10: \n
		if(stream > 64 && stream < 91) {
			stream -= 65;
		} else if(stream == 32) {
			// space
			stream = 26;
		}
		list = prepend(list, stream);
		stream = fgetc(fin);
	}

	//Remove trailing whitespace
	if(list->next->data == 26) {
		List * retnode = list->next;
		list->next = retnode->next;
		free(retnode);
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

// Computes A + B
// O(n), n being the number of digits output will have
List * add(List * a, List * b) {
	// Assume both numbers are positive or both are negative
	// Get the signs
	int ka = a->data;
	int kb = b->data;
	int signa = ka;
	int signb = kb;
	int signsum = 1;

	if(signa < 0) signa *= -1;
	if(signb < 0) signb *= -1;

	int k = signa;
	if(signb > k) k = signb;

	if((signa != ka) ^ (signb != kb)) {
		// AB < 0
		if(signa > signb) {
			// |a| > |b|
			signa = 1;
			signb = -1;
			if(ka < 0) signsum = -1; //If the bigger number is negative
			else signsum = 1;
		} else {
			// |b| > |a|
			signa = -1;
			signb = 1;
			if(kb < 0) signsum = -1; //If the bigger number is negative
			else signsum = 1;
		}
	} else {
		// AB >= 0
		signa = 1;
		signb = 1;
		if(ka < 0) signsum = -1; //If a and b are negative
		else signsum = 1;
	}

	k++;
	int c = 0; // Carryover
	int s = 0; // Sum mod 10
	int i = 0; // Iterator
	int t = 0; // Digit sum
	List * sum = NULL;
	sum = init();
	List * sumtail = sum;
	List * ai = a->next;
	List * bi = b->next;
	int adata = 0;
	int bdata = 0;

	for(; i < k-1; i++) {
		if(ai == NULL && bi == NULL) break;
		if(ai == NULL){
			adata = 0;
		} else {
			adata = ai->data;
			ai = ai->next;
		}

		if(bi == NULL){
			bdata = 0;
		} else {
			bdata = bi->data;
			bi = bi->next;
		}

		t = (signa*adata) + (signb*bdata) + c;
		s = t % 10; // Get the digit
		c = t / 10; // Update the carryover

		// Append s to the sum
		sumtail = append(sum, sumtail, s);
	}

	// Add carryover if it isn't just 0
	if(c) {
		sumtail = append(sum, sumtail, c);
	}

	return sum;
}

// Computes AB (might be inefficient; can be optimized later)
// O(n^2), n being the number of digits of a and b
List * mult(List * a, List * b) {
	// Worry about signs and combing out the product later
	int p = 0; // Product of digits mod 10
	int t = 0; // Product of digits
	int c = 0; // Carryover

	// Keep track of how many ->next's pi and pj will make
	// Size of number = pi + pj
	int isteps = 0; // Steps *pi has made
	int jsteps = 0; // Steps *pj has made

	// Pointers in the list
	List * product = NULL;
	product = init();
	List * producttail = product;
	// Initially 0->0->NULL
	producttail = append(product, producttail, 0);
	List * pi = product->next; // Iterator for list a
	List * pj = product->next; // Iterator for list b
	List * ai = a->next; // Iterator along list a
	List * bj = b->next; // Iterator along list b

	while(ai != NULL) {
		c = 0;
		pj = pi; // Move pj to where pi is now
		bj = b->next;
		while(bj != NULL) {
			t = (ai->data)*(bj->data) + (pj->data) + c;
			pj->data = t % 10;
			c = t / 10;

			//Debugging
			//printf("%dx%d\n", ai->data, bj->data);

			// Move the stuff
			if(pj->next == NULL) {
				producttail = append(product, producttail, 0);
			}
			pj = pj->next;
			bj = bj->next;
		}
		pj->data += c;

		// Move the stuff
		if(pi->next == NULL) {
			producttail = append(product, producttail, 0);
		}
		pi = pi->next; // Might be reason for a segfault
		ai = ai->next; // Move to the next digit of a
	}

	// Remove the trailing zero?
	if(producttail->data == 0) {
		while(pi != NULL && pi->next != NULL && pi->next != producttail) {
			pi = pi->next;
		}
		if(pi->next == producttail) {
			free(producttail);
			producttail = pi;
			pi->next = NULL;
			product->data -= 1;
		}
	}
	return product;
}

// Computes A - B
// O(n), same as add
List * sub(List * a, List * b) {
	a->data *= -1;
	List * amb = add(a, b);
	a->data *= -1;
	return amb;
}

List * base10to27(List * a) {

}

// Might be a bottleneck
List * base27to10(List * a) {
	List * b = intToList(27);
	List * powerb = intToList(1);
	List * oldpower = powerb; // Holds the old power of b
	List * digita = a->next; // Holds the digit of a (b27)
	List * output = init(); // Holds the output list
	List * oldout = output; // Holds the old output (adding creates a new list)
	List * tempout = NULL; // Holds the partial output (digit * power of b)
	List * hpdigita = NULL; // Holds the list representation of digit of a
	while(digita != NULL) {
		hpdigita = intToList(digita->data); // Digit of a in list form
		tempout = mult(hpdigita, powerb); // Partial outuput

		output = add(output, tempout); // Add partial output to total output
		freeList(oldout); // Free the old output
		oldout = output; // Set the new old output

		powerb = mult(powerb, b);
		freeList(oldpower);
		oldpower = powerb;
		digita = digita->next; // Get the next digit

		freeList(hpdigita);
	}

	freeList(powerb);
	freeList(b);
	return output;
}

void main() {
	// Declarations
	FILE * fin;
	FILE * fout;
	fin = fopen("testinput.txt", "r");
	fout = fopen("201508086.txt", "w");

	char filler[FILLER_SIZE]; //Stores the useless text (eg. Alice / Bob / etc.)
	filler[0] = 'Z';
	List * p = init();
	List * q = init();
	List * e = init();
	List * m = init();

	// Testing variable
	List * pandq = NULL;
	List * porq = NULL;
	
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

			//Check if the addition fxn is working
			porq = add(p,q);
			printNumber(porq);
			freeList(porq);
			pandq = mult(p,q);
			printNumber(pandq);
			freeList(pandq);
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
