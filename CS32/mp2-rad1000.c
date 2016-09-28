#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILLER_SIZE 50
#define RADIX 1000
#define RADIXSIZE 3
// 0 to 999,999,999 (9 digits)
// Base 10
// Circular doubly linked list with list head

// -1 % 10 = 9 not -1
int mod(int a, int b) {
	int c = a % b;
	if(c<0) c += b;
	return c;
}

// For addition / subtraction
int carryover(int a, int b) {
	if((a>0 && b>0) || (a<0 && b<0)) return a / b;
	else return a;
}

typedef struct List {
	int data;
	struct List * next;
	struct List * prev;
} List;

List * init() {
	List * out = (List*) malloc(sizeof(List));
	out->data = 0; // Size of the list
	out->next = out;
	out->prev = out;
	return out;
}

// Prepend puts the new digit between the list head and first digit
// Use when reading from highest to lowest place value
List * prepend(List * list, int data) {
	List * newnode = (List*) malloc(sizeof(List));
	newnode->data = data;
	
	newnode->next = list->next;
	newnode->next->prev = newnode;

	list->next = newnode;
	newnode->prev = list;

	//Update size of list
	list->data = list->data + 1;
	return list;
}

// Append puts the new digit at the end
// Use when reading from lowest to highest place value
// O(1)
List * append(List * list, int data) {
	List * tail = list->prev;
	// If new list, set the highest place value
	List * newnode = (List*) malloc(sizeof(List));
	newnode->data = data;
	newnode->next = list;
	list->prev = newnode;

	tail->next = newnode;
	newnode->prev = tail;
	tail = newnode;

	//Update size of list
	list->data = list->data + 1;
	return list;
}

// O(e), e = number of digits of n
// radix is 1,000,000,000
List * intToList(int n) {
	// Assume representation in base 10
	List * output = init();
	int modu = 0;
	while(n > 0) {
		// mod = n % RADIX; // Ones digit
		modu = mod(n, RADIX);
		output = append(output, modu);
		n = n / RADIX; // Remainder
	}
	return output;
}

// O(n)
List * freeList(List * list) {
	List * ptr = list->next;
	List * head = list;
	list = ptr;
	while(ptr != head) {
		list = list->next;
		free(ptr);
		ptr = list;
	}
	free(ptr);
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
	char stream[] = {'$', '\0'};
	int numstream = -1;
	int radixstream = 0;
	int radix = RADIX / 10;
	while(stream[0] != ',' && stream[0] != '\n') {
		// Reset values
		radixstream = 0;
		radix = RADIX/10;
		// Read the radix-1B number
		while(radix > 0) {
			stream[0] = (char) fgetc(fin);
			if(stream[0] == ',' || stream[0] == '\n' || stream[0] == ' ') break;
			numstream = atoi(stream);
			if(numstream == 0 && stream[0] != '0') {
				stream[0] = ',';
				break; // Nonnumber detected
			}
			//printf("|%s|%d|%d|\n", stream, numstream, radix);
			radixstream += numstream*radix;
			radix /= 10;
			numstream = 0;
		}
		//printf(":%d:\n", radixstream);

		// Append number to list
		if(radixstream != 0) list = prepend(list, radixstream);
	}
	//printf("|%d|\n", radix);

	// Shift the digits if necessary
	radix *= 10;
	if(radix>0 && radix<RADIX) {
		List * shift_ptr = list->next;
		int shiftee = 0;
		int shiftee_offset = RADIX / radix;
		while(shift_ptr != list) {
			shift_ptr->data /= radix;
			if(shift_ptr->next != list) shiftee = shift_ptr->next->data % radix;
			else shiftee = 0;
			shiftee *= shiftee_offset;
			shift_ptr->data += shiftee;
			shift_ptr = shift_ptr->next;
			shiftee = 0;
		}
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
		list->next->prev = list;
		free(retnode);
		list->data -= 1;
	}
	return fin;
}

void printNumber(List * num) {
	// In reverse
	printf("%d::", num->data);
	List * ptr = num->next;
	while(ptr != num) {
		printf("%d.", ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
	return;
}

void printNumberCorrect(List * num) {
	List * tail = num->prev;
	if(num == tail) {
		printf("0\n");
		return;
	}

	List * tailptr = tail;
	while(tailptr != num) {
		// Print zero padding
		if(tailptr != tail) printf("%03d", tailptr->data);
		else printf("%d", tailptr->data);
		tailptr = tailptr->prev;
	}
	printf("\n");
	return;
}

void printMessage(List * msg) {
	printf("%d::", msg->data);
	List * ptr = msg->next;
	char stream = '%';
	while(ptr != msg) {
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

// Compares A and B (+ if A is bigger, - if B is bigger, 0 otherwise)
int compare(List * a, List * b) {
	List * atail = a->prev;
	List * btail = b->prev;
	if(a->data != b->data) return a->data - b->data; //Covers the cases when a and b are negative
	if(a->data == 0) return 0;

	while(atail != a) {
		if(atail->data != btail->data) return atail->data - btail->data;
		atail = atail->prev;
		btail = btail->prev;
	}
	return 0;
}

// Computes A + B
// O(n), n being the number of digits output will have
List * add(List * a, List * b) {
	// Instantiate atail and btail
	List * atail = a->prev;
	List * btail = b->prev;
	// Assume both numbers are positive or both are negative
	// Get the signs
	int ka = a->data; // Stores number of digits (pos or neg depending on a)
	int kb = b->data;
	int signa = ka; // Stores abs(ka) first, then the sign of a
	int signb = kb;
	int signsum = 1; // Stores the final sign of the sum

	if(signa < 0) {
		a->data *= -1; // for |a| comparison
		signa *= -1;
	}
	if(signb < 0) {
		b->data *= -1; // for |b| comparison
		signb *= -1;
	}

	int k = signa;
	if(signb > k) k = signb;

	// Faulty comparison of |a| and |b|; change later if needed
	if((ka < 0) ^ (kb < 0)) {
		// AB < 0
		if(compare(a, b) > 0) {
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

	// Restore values of a->data and b->data from the abs() calc.
	a->data = ka;
	b->data = kb;

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
		if(ai == a && bi == b) break;
		if(ai == a){
			adata = 0;
		} else {
			adata = ai->data;
			ai = ai->next;
		}

		if(bi == b){
			bdata = 0;
		} else {
			bdata = bi->data;
			bi = bi->next;
		}

		t = (signa*adata) + (signb*bdata) + c;
		// s = t % 10; // Get the digit
		s = mod(t, RADIX);
		// c = t / 10; // Update the carryover
		c = carryover(t, RADIX);
		//printf("%d|%d\n", s, c);

		// Append s to the sum
		sum = append(sum, s);
	}

	// Add carryover if it isn't just 0
	if(c) {
		sum = append(sum, c);
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
	// Initially 0->0->NULL
	product = append(product, 0);
	List * pi = product->next; // Iterator for list a
	List * pj = product->next; // Iterator for list b
	List * ai = a->next; // Iterator along list a
	List * bj = b->next; // Iterator along list b

	while(ai != a) {
		c = 0;
		pj = pi; // Move pj to where pi is now
		bj = b->next;
		while(bj != b) {
			t = (ai->data)*(bj->data) + (pj->data) + c;
			// pj->data = t % 10;
			pj->data = mod(t, RADIX);
			c = t / RADIX;

			//Debugging
			//printf("%dx%d\n", ai->data, bj->data);

			// Move the stuff
			if(pj->next == product) {
				product = append(product, 0);
			}
			pj = pj->next;
			bj = bj->next;
		}
		pj->data += c;

		// Move the stuff
		if(pi->next == product) {
			product = append(product, 0);
		}
		pi = pi->next; // Might be reason for a segfault
		ai = ai->next; // Move to the next digit of a
	}

	// Remove the trailing zero?
	List * producttail = product->prev;
	while(producttail->data == 0) {
		pi = producttail->prev;

		pi->next = product;
		product->prev = pi;
		free(producttail);
		producttail = pi;
		product->data -= 1;
	}

	// Set if positive or negative (NONE YET)
	return product;
}

// Computes A - B
// O(n), same as add
List * sub(List * a, List * b) {
	b->data *= -1;
	List * amb = add(a, b);
	b->data *= -1;
	return amb;
}

List * base10to27(List * a) {
	// None yet
}

// Might be a bottleneck
// To be optimized (storing powers of 27 somewhere)
List * base27to10(List * a) {
	List * b = intToList(27);
	List * powerb = intToList(1);
	List * oldpower = powerb; // Holds the old power of b
	List * digita = a->next; // Holds the digit of a (b27)
	List * output = init(); // Holds the output list
	List * oldout = output; // Holds the old output (adding creates a new list)
	List * tempout = NULL; // Holds the partial output (digit * power of b)
	List * hpdigita = NULL; // Holds the list representation of digit of a
	while(digita != a) {
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

// O(pretty fucking big)
// Takes in e and phin s.t. e*x + phin*y = 1, returns x
List * extendedEuclidean(List * e, List * phin) {
	
}

void test() {
	// WORKS: Reading numbers, addition, subtraction (wrong on sign)
	FILE * ftest = fopen("test.txt", "r");
	List * a = NULL;
	List * b = NULL;
	List * c = NULL;
	while(!feof(ftest)) {
		a = init();
		b = init();
		ftest = readNumber(ftest, a);
		ftest = readNumber(ftest, b);
		printNumberCorrect(a);
		printNumberCorrect(b);
		c = add(a,b);
		printf("c = ");
		printNumberCorrect(c);
		a = freeList(a);
		b = freeList(b);
		c = freeList(c);
	}
	fclose(ftest);
	return;
}

void main() {
	// testing realm
	test();
	return;
	// Declarations
	FILE * fin;
	FILE * fout;
	fin = fopen("testinput.txt", "r");
	fout = fopen("201508086.txt", "w");

	char filler[FILLER_SIZE]; //Stores the useless text (eg. Alice / Bob / etc.)
	filler[0] = 'Z';
	List * one = init();
	one = prepend(one, 1);
	List * p = NULL;
	List * pmo = NULL;
	List * q = NULL;
	List * qmo = NULL;
	List * e = NULL;
	List * m = NULL;
	List * n = NULL;
	List * phin = NULL;

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
			pmo = freeList(pmo);
			qmo = freeList(qmo);
			n = freeList(n);
			p = init();
			q = init();
			e = init();
			pmo = init();
			qmo = init();
			n = init();

			// Parse p,q,e
			fin = readNumber(fin, p);
			fin = readNumber(fin, q);
			fin = readNumber(fin, e);

			//Check if tama pagkabasa
			printf("/%s\\\n", filler);
			printNumberCorrect(p);
			printNumberCorrect(q);
			printNumberCorrect(e);

			//Check if the addition fxn is working
			/*
			porq = add(p,q);
			printNumber(porq);
			freeList(porq);
			pandq = mult(p,q);
			printNumber(pandq);
			freeList(pandq);
			*/

			// Get n
			n = mult(p,q);
			printf("n = ");
			printNumberCorrect(n);

			// Get phi(n)
			pmo = sub(p, one);
			qmo = sub(q, one);
			printf("p-1 = ");
			printNumberCorrect(pmo);
			printf("q-1 = ");
			printNumberCorrect(qmo);
			phin = mult(pmo, qmo);
			printf("phi(n) = ");
			printNumberCorrect(phin);
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
	n = freeList(n);
	fclose(fin);
	fclose(fout);
}
