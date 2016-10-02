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
	if(a > 0) return a / b; //Addition
	else return a ? -1 : 0; //Subtraction
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

// Delete end removes least significant digits (opposite of prepend)
List * deleteRight(List * list) {
	List * retnode = list->next;
	list->next = retnode->next;
	list->next->prev = list;
	free(retnode);
	list->data -= 1;
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

// Duplicate list
// UNTESTED !!!!!!!!!!
List * duplicate(List * n) {
	List * new = init();
	List * ptr = n->next;
	while(ptr != n) {
		new = append(new, ptr->data);
		ptr = ptr->next;
	}
	return new;
}

// O(n)
List * freeList(List * list) {
	if(list == NULL) return NULL;
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
		if(feof(fin)) break;
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
	while(!feof(fin) && stream[0] != ',' && stream[0] != '\n') {
		// Reset values
		radixstream = 0;
		radix = RADIX/10;
		// Read the radix-1B number
		while(radix > 0) {
			stream[0] = (char) fgetc(fin);
			if(feof(fin)) break;
			//printf("%s:stream, %d:feof\n", stream, feof(fin));
			if(stream[0] == ',' || stream[0] == '\n' || stream[0] == ' '){
				break;
			}
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
		list = prepend(list, radixstream);
	}
	//printf("|%d|\n", radix);

	// A 1000 | n number won't be read anyway; remove trailing zeroes (right)
	List * retnode = list->next;
	while(retnode != list && retnode->data == 0) {
		list->next = retnode->next;
		list->next->prev = list;
		free(retnode);
		retnode = list->next;
		list->data -= 1;
	}

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

	// Remove trailing zeroes (left)
	retnode = list->prev;
	while(retnode != list && retnode->data == 0) {
		list->prev = retnode->prev;
		list->prev->next = list;
		free(retnode);
		retnode = list->prev;
		list->data -= 1;
	}
	return fin;
}

FILE * readMessage(FILE * fin, List * list) {
	// Declarations
	int stream = -1;
	stream = fgetc(fin);
	while(stream != 116 && stream != 10 && stream != 102) { //116: t; 10: \n
		if(feof(fin)) break;
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
		printf("%d::0\n", num->data);
		return;
	}

	List * tailptr = tail;
	//printf("%d::", num->data);
	// Print negative
	if(num->data < 0) printf("-");
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

	int k = signa; // For determining max number of digits
	if(signb > k) k = signb;

	// Faulty comparison of |a| and |b|; change later if needed
	//printf("%d;%d\n", ka, kb);
	//printf("comp: %d\n", compare(a,b));
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
	//printf("ss:%d\n", signsum);

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
		//printf("%d|%d|%d\n", t, s, c);

		// Append s to the sum
		sum = append(sum, s);
	}

	// Add carryover if it isn't just 0
	if(c) {
		sum = append(sum, c);
	}

	//update signsum
	sum->data *= signsum;

	// Trailing zeroes
	List * retnode = sum->prev;
	while(retnode->data == 0 && retnode != sum) {
		sum->prev = retnode->prev;
		sum->prev->next = sum;
		free(retnode);
		retnode = sum->prev;
		if(sum->data > 0) sum->data -= 1;
		else sum->data += 1;
	}

	return sum;
}

// Computes AB (might be inefficient; can be optimized later)
// O(n^2), n being the number of digits of a and b
List * mult(List * a, List * b) {
	// If one of them is 0
	if(a->data == 0 || b->data == 0) return init();
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
	if((a->data < 0) ^ (b->data < 0)) product->data *= -1;
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

// Computes "bitshifting" (-n implies to right, vv.)
List * shift(List * a, int n) {
	// If shifting to the left (* RADIX)
	while(n > 0) {
		a = prepend(a, 0);
		n--;
	}
	// If shifting to the right (/ RADIX)
	while(n < 0) {
		// Delete least significant digits
		a = deleteRight(a);
		n++;
	}
	return a;
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

// O(mygod)
// Finds estimate for reciprocal of d times b^2e
// NOTE: in modulus and div, the "exponent" is actually 2(e+1) because of indexing
List * NewtonRhapson(List * d, int two_e) {
	// Generate x0 first
	int power_x0 = d->data;
	if(power_x0 > 0) power_x0 *= -1;
	power_x0 += two_e;
	//power_x0 -= 1; // F A U L T Y M A T H
	List * x0 = intToList(1);
	x0 = shift(x0, power_x0);
	List * two_b2e = intToList(2);
	two_b2e = shift(two_b2e, two_e);
	//printf("precision of recip: %d\n", power_x0);

	// Declare delta_x and other list items
	List * x = NULL;
	List * delta_x = intToList(1);
	List * deltaret = delta_x;
	List * dx0 = NULL;
	List * x0prod = NULL;
	List * x0ret = x0;
	/*printf("precond: (%d:powerx0) ", power_x0);
	printNumberCorrect(x0);
	printf("2*b^2e: ");
	printNumberCorrect(two_b2e);
	printf("denom: ");
	printNumberCorrect(d);*/

	while(delta_x->data != 0) {
		dx0 = mult(d, x0); // d * x0
		x0prod = sub(two_b2e, dx0); // 2b^2e - dx0
		x = mult(x0, x0prod); // x0 * etc.
		//printf("b4shift: ");
		//printNumberCorrect(x);
		x = shift(x, -1*two_e); // div by b^2e
		delta_x = sub(x, x0);
		//printf("iterx: ");
		//printNumberCorrect(x);

		// reset the lists
		x0 = x; // Move x0 up the sequence. as of now x and x0 are same
		freeList(dx0);
		freeList(x0prod);
		freeList(x0ret);
		freeList(deltaret);
		x0ret = x0; //Prepare for freeing
		deltaret = delta_x;
	}

	// return x
	freeList(delta_x);
	freeList(two_b2e);
	return x;
}

// O()
// Computes [a/b] with NewtonRhapson
List * divide(List * a, List * b) {
	int bprec = a->data; // P R E C I S I O N
	List * hack = intToList(10);
	List * hack_b_recip = NULL;
	if(bprec < 0) bprec *= -1;
	int k = bprec + 1; // Muh precision
	int two_k = k*2; // Gimme that sweet sweet P R E C I S I O N
	List * b_recip = NewtonRhapson(b, two_k);
	// WARNING: HACK
	hack_b_recip = b_recip;
	b_recip = add(hack_b_recip, hack);
	//printf("100../b = ");
	//printNumberCorrect(b_recip);
	List * adivb = mult(a, b_recip);
	//printf("a*100../b = ");
	//printNumberCorrect(adivb);
	//printf("precision of revert: %d\n", two_k-bprec);
	adivb = shift(adivb, -1*two_k);
	freeList(b_recip);
	freeList(hack);
	freeList(hack_b_recip);
	return adivb;
}

// O(hno)
// Does modulo but in radix
List * radixModulo(List * x, int power_m) {
	// Basically preserve the power_m least significant digits
	List * ptr = x->next;
	List * output = init();
	while(ptr != x && power_m > 0) {
		output = append(output, ptr->data);
		ptr = ptr->next;
		power_m--;
	}
	return output;
}

//O(tanginang froot loops)
// Returns r = x mod m
// Does Barrett Reduction if necessarcy
// NEEDS: NewtonRhapson, shift
// BARRETTS ONLY WORKS FOR x < m^2 TAKE NOTE OF THIS
List * modulus(List * x, List * m, List * mu) {
	if(x->data < 0) {
		List * xnew = x;
		List * xret = x;
		while(xnew->data < 0) {
			xnew = add(xnew,m);
			if(xret != x)freeList(xret);
			xret = xnew;
		}
		return xnew;
	}
	if(compare(m, x) >= 0) return duplicate(x); // If x < m
	// Get k
	int k = m->data;
	if(k<0) k*=-1;
	int two_k = k * 2;

	// Get mu
	if(mu == NULL) {
		mu = NewtonRhapson(m, two_k);
	}

	// Instantiate q1, q2, q3, etc.
	List * q1 = duplicate(x);
	q1 = shift(q1, -1*(k-1));
	List * q3 = mult(q1, mu);
	q3 = shift(q3, -1*(k+1));
	/*
	printf("\nq1: ");
	printNumberCorrect(q1);
	printf("\nq3: ");
	printNumberCorrect(q3);
	printf("\nmu: ");
	printNumberCorrect(mu);
	printf("\nm: ");
	printNumberCorrect(m);
	*/
	freeList(q1);
	freeList(mu);

	List * r1 = radixModulo(x, k+1);
	List * r2 = mult(q3, m);
	/*
	printf("\nr1: ");
	printNumberCorrect(r1);
	printf("\nr2 ");
	printNumberCorrect(r2);
	*/
	List * r3 = sub(r1, r2);
	/*
	printf("\nr1: ");
	printNumberCorrect(r1);
	printf("\nr2 ");
	printNumberCorrect(r2);
	printf("\nr3: ");
	printNumberCorrect(r3);*/
	freeList(r1);
	freeList(r2);
	freeList(q3);

	return r3;
}

// O(pretty fucking big)
// Takes in e and phin s.t. e*x + phin*y = 1, returns x
// TOO LAZY TO TEST NEWFOUND HACK FOR DIV PRECISION AHAHAHAHA
List * extendedEuclidean(List * e, List * phin) {
	List * t = intToList(0);
	List * newt = intToList(1);
	List * tret = t;
	List  * r = duplicate(phin);
	List * newr = duplicate(e);
	List * rret = r;
	List * q = NULL;
	List * qt = NULL;
	List * qr = NULL;
	while(newr->data != 0) {
		// Prepare for freeing
		freeList(q);
		rret = r;
		tret = t;

		// Do math
		q = divide(r, newr);
		t = newt;
		qt = mult(q, newt);
		newt = sub(tret, qt);
		r = newr;
		qr = mult(q, newr);
		newr = sub(rret, qr);

		// Free
		freeList(rret);
		freeList(tret);
		freeList(qr);
		freeList(qt);
	}
	if(r->data == 1 && r->next->data == 1) {
		// Make t positive
		while(t->data < 0) {
			tret = t;
			t = add(tret, phin);
			freeList(tret);
		}
		return t;
	} else {
		printf("YOU JUST GOT Z E E ' D\n");
		return init(); // Or null?
	}
}

// O(gadududu push pineapple shake the tree)
// MONTGOMERY FUNCTIONS
// Precompute ModInv of R mod m
List * modInvOfR(List * m) {
	int power_r = m->data;
	if(power_r < 0) power_r *= -1;
	List * R = intToList(1);
	R = shift(R, power_r);
	List * Rinv = extendedEuclidean(R, m);
	freeList(R);
	return Rinv;
}

List * modInvOfMO(List * m) {
	if(m->data == 0) return NULL;
	List * m0 = intToList(m->next->data);
	List * B = intToList(RADIX);
	List * m0_modinv = extendedEuclidean(m0, B);
	m0_modinv->data *= -1;
	List * m0_modinvmod = modulus(m0_modinv, B);
	return m0_modinvmod;
}

List * changeToMontgo(List * x, List * m, List * MU) {
	int power_r = m->data;
	if(power_r < 0) power_r *= -1;
	List * R = intToList(1);
	R = shift(R, power_r);
	List * Rmod = sub(R, m);
	List * product = mult(x, Rmod);
	List * productmod = modulus(product, m, MU);
	freeList(R);
	freeList(Rmod);
	freeList(product);
	return productmod;
}

List * changeFromMontgo(List * x, List * m, List * MU, List * RINV) {
	List * product = mult(x, RINV);
	List * productmod = modulus(product, m, MU);
	return productmod;
}

List * multMontgo(List * xl, List * yl, int power_r, List * m, List * m0_recip) {
	List * productl = mult(xl, yl);
	List * productl_digit = NULL;
	List * ptr = productl->next;
	List * k = NULL;
	List * mk = NULL;
	List * kmod = NULL;
	List * productlret = NULL;
	for(int pr = power_r; pr >0; pr--) {
		productlret = productl;
		productl_digit = intToList(ptr->data);
		k = mult(productl_digit, m0_recip);
		kmod = radixModulo(k, 1);
		mk = mult(m, kmod);
		productl = add(productlret, mk);

		//free
		freeList(productlret);
		freeList(k);
		freeList(kmod);
		freeList(mk);
		freeList(productl_digit);
	}

	productl = shift(productl, -1*power_r);
	return productl;
}

void test() {
	// WORKS: Reading numbers, addition, subtraction, multiplication (?)
	// Might have bugs: Reciprocation, Division, Modulo (INC)
	// 27 to 10
	FILE * ftest = fopen("test.txt", "r");
	List * a = NULL;
	List * b = NULL;
	List * c = NULL;
	List * d = NULL;
	List * pm1 = NULL;
	List * qm1 = NULL;
	List * phin = NULL;
	List * one = intToList(1);
	int twoe = 0;
	while(1) {
		a = init();
		b = init();
		c = init();
		if(feof(ftest)) break;
		ftest = readNumber(ftest, a);
		if(a->data == 0) break;
		ftest = readNumber(ftest, b);
		if(b->data == 0) break;
		ftest = readNumber(ftest, c);
		pm1 = sub(a, one);
		qm1 = sub(b, one);
		phin = mult(pm1, qm1);
		d = extendedEuclidean(c,phin);
		//printf("c = ");
		printNumberCorrect(c);
		//printf("d = ");
		if(d!=NULL) printNumberCorrect(d);
		a = freeList(a);
		b = freeList(b);
		c = freeList(c);
		d = freeList(d);
		freeList(pm1);
		freeList(qm1);
		freeList(phin);
		printf("\n");
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
	fin = fopen("test.txt", "r");
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
			phin = freeList(phin);
			p = init();
			q = init();
			e = init();
			//pmo = init();
			//qmo = init();
			//n = init();

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
			porq = add(p,q);
			printNumberCorrect(porq);
			freeList(porq);
			pandq = sub(p,q);
			printNumberCorrect(pandq);
			freeList(pandq);

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
