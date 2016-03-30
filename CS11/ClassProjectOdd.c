#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define IOSHORT 10 //for integers
#define IOMED 50 //for long integers and others
#define IOLONG 200

/*
    short:  2 bytes,    -32,768 to 32,767
    ushort: 2 bytes,    0 to 65,535
    long:   4 bytes,    -2,147,483,648 to 2,147,483,647
    ulong:  4 bytes,    0 to 4,294,967,295
*/

/*
    *****************************************************************************
    ** LINKED-LIST FUNCTIONS / STRUCTURES ***************************************
    ** Functions / structures which involve linked lists ************************
    *****************************************************************************
*/

typedef struct LinkedList{
    int val;
    struct LinkedList * next;
} List;

typedef struct PtrLinkedList{
    void * data;
    struct PtrLinkedList * next;
} AllPurposeList;

AllPurposeList * createAPList(AllPurposeList * head, void * data, int type){ //0 = NULL, 1 = int, 2 = char, 3 = string, 4 = float
    head = (AllPurposeList*) malloc(sizeof(AllPurposeList));
    switch(type){
        case 0: head->data = NULL; break;
        case 1: head->data = (int*) malloc(sizeof(int)); break;
        case 2: head->data = (char*) malloc(sizeof(char)); break;
        case 3: head->data = (char*) malloc(sizeof(char)*IOMED); break;
        case 4: head->data = (float*) malloc(sizeof(float)); break;
    }
    head->next = NULL;
    return head;
}

AllPurposeList * prependAPList(AllPurposeList * head, void * data, int type){
    if(!head){
        return createAPList(head, data, type);
    } else {
        AllPurposeList * node = (AllPurposeList*) malloc(sizeof(AllPurposeList));
        node->data = data;
        node->next = head;
        return node;
    }
}

AllPurposeList * appendAPList(AllPurposeList * head, void * data, int type){
    if(!head){
        return createAPList(head, data, type);
    } else {
        AllPurposeList * node = (AllPurposeList*) malloc(sizeof(AllPurposeList));
        node->data = data;
        node->next = NULL;
        head->next = node;
        return head;
    }
}

/*
    *****************************************************************************
    ** ALL-PURPOSE FUNCTIONS / STRUCTURES ***************************************
    ** Functions / structures which may be used by a lot of other subprograms. **
    *****************************************************************************
*/

int isNotInteger(char * input, int * num, int program){ //if not a program variable, then program = 0
    *num = atoi(input);
    return 0;
}

int isNotFloat(char * input, float * num, int program){
    *num = atoi(input); //not really but eh
    return 0;
}

void printIntArr(int * arr, int num){
    int x;
    printf("[");
    for(x=0; x<num; x++){
        printf("%s%d", x ? ", " : "", *(arr + x));
    }
    printf("]\n");
}

void printFloatArr(float * arr, int num){
    int x;
    printf("[");
    for(x=0; x<num; x++){
        printf("%s%.3f", x ? ", " : "", *(arr + x));
    }
    printf("]\n");
}

void trim(char * string){
	int ndx_s = 0; /*start of string*/
	int ndx_e = strlen(string) - 1; /*end of string*/

	/*Removes whitespaces after text*/
	while(*(string+ndx_e) == ' ' || *(string+ndx_e) == '\t' || *(string+ndx_e) == '\n'){
		*(string+ndx_e) = '\0';
		ndx_e--;
	}
	ndx_e++;

	int ndx_s_out = 0; /*start of string w/o whitespaces*/
	for(ndx_s = 0; ndx_s <= ndx_e; ndx_s++){
		if(*(string+ndx_s) == ' ' || *(string+ndx_s) == '\t' || *(string+ndx_s) == '\n'){
			ndx_s_out++;
		} else {
			break;
		}
	}

	/*shifting of characters, removing whitespace*/
	if(ndx_s_out){
		for(ndx_s = 0; ndx_s + ndx_s_out <= ndx_e; ndx_s++){
			*(string+ndx_s) = *(string+ndx_s+ndx_s_out);
		}
	}
}

int * processInputInt(char * string, int * output, int * len){
    int ctr = 0;
    output = (int*) malloc(sizeof(int)*IOMED);
    char del = ',';
    char * tk = strtok(string, &del);
    while(tk){
        *(output + ctr) = atoi(tk);
        tk = strtok(NULL, &del);
        ctr++;
        if(ctr%IOMED == 0){
            output = (int*) realloc(output, sizeof(int)*IOMED + ctr);
        }
    }
    *len = ctr;
    return output;
}

float * processInputFloat(char * string, float * output, int * len){
    int ctr = 0;
    output = (float*) malloc(sizeof(float)*IOMED);
    char del = ',';
    char * tk = strtok(string, &del);
    while(tk){
        *(output + ctr) = atof(tk);
        tk = strtok(NULL, &del);
        ctr++;
        if(ctr%IOMED == 0){
            output = (float*) realloc(output, sizeof(float)*IOMED + ctr);
        }
    }
    *len = ctr;
    return output;
}

int powInt(int base, int exp){
    int ret = 1;
    while(exp){
        ret *= base;
        exp--;
    }
    return ret;
}

float distance(float x1, float x2, float y1, float y2){ //x = x1-x2, y = y1-y2
    float x = x1 - x2;
    float y = y1 - y2;
    return sqrt((double) ((x*x) + (y*y)));
}

float min(float a, float b){
    return a < b ? a : b;
}

float minrec(float * set, int len){
    float minf;
    if(len == 1){
        return *set;
    } else if(len == 2){
        return *(set+1) < *set ? *(set+1) : *set;
    } else {
        minf = minrec(set+1, len-1);
        return *set < minf ? *set : minf;
    }
}

float max(float a, float b){
    return a > b ? a : b;
}

float maxrec(float * set, int len){
    float minf;
    if(len == 1){
        return *set;
    } else if(len == 2){
        return *(set+1) > *set ? *(set+1) : *set;
    } else {
        minf = maxrec(set+1, len-1);
        return *set > minf ? *set : minf;
    }
}

/*
    ********************************************************************
    ** PROGRAM FUNCTIONS ***********************************************
    ** The 20 subprograms, along with extra functions related to them **
    ********************************************************************
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program1(){
    printf("\nProgram 1: Trailing Zeroes\n");
    long long int n;
    printf("Enter a number: ");
    scanf("%lld", &n);
    int d = 5, ans = 0;
    while(d <= n){
        ans += n / d;
        d *= 5;
    }
    printf("The number %lld! has %d trailing zeroes.\n", n, ans);
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program3(){
    //TODO: check if x^1 is ok
    printf("\nProgram 3: Prime Factorization\n");
    unsigned long int n, factor = 2;
    int power = 0;
    printf("Enter number: ");
    scanf("%ld", &n);
    for(;factor<=n;factor++){
        if(n%factor==0){
            power++;
            n /= factor;
            factor--;
        } else {
            if(power){
                printf("%ld^%d x ", factor, power);
            }
            power = 0;
        }
    }
    printf("%ld^%d\n", factor, power);
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program5(){
    //TODO: IDK
    printf("\nProgram 5: Multiplying polynomials\n");
    char poly1[IOMED], poly2[IOMED];
    char * token;
    int coef1 = 0, coef2 = 0, prod;
    printf("Enter the first polynomial coefficients.\nStart from the highest degree, and separate coefficients with a comma: ");
    fgets(poly1, IOMED, stdin);
    printf("Enter the second polynomial coefficients.\nStart from the highest degree, and separate coefficients with a comma: ");
    fgets(poly2, IOMED, stdin);
    //get the coefficients
    token = strtok(poly1, ",");
    while(token){
        coef1 *= 10;
        coef1 += atoi(token);
        token = strtok(NULL, ",");
    }

    token = strtok(poly2, ",");
    while(token){
        coef2 *= 10;
        coef2 += atoi(token);
        token = strtok(NULL, ",");
    }

    prod = coef1 * coef2;
    printf("coef1:%d, coef2:%d, prod:%d\n", coef1, coef2, prod);
    int dorp = 0; //reverse of prod for coeff output
    while(prod){
        dorp *= 10;
        dorp += prod % 10;
        prod /= 10;
    }

    printf("The polynomial in coeff form is: ");
    while(dorp){
        printf("%d", dorp % 10);
        dorp /= 10;
        if(dorp) printf(",");
    }
    printf("\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program7(){
    printf("\nProgram 7: Reciprocals\n");
    int d;
    printf("Enter a number: ");
    scanf("%d", &d);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int fact(int n){
    if(n == 0){
        return 1;
    } else if(n == 1){
        return 1;
    } else {
        return n * fact(n-1);
    }
}

void program9(){
    printf("\nProgram 9: Pascal's Triangle");
    int n, b, result;
    int f1, f2, f3;
	printf("\nEnter nth line: ");
	scanf("%d", &n);
	for (b=0;b<=n;b++)
	{
        f1 = fact(n);
        f2 = fact(b);
        f3 = fact(n-b);
		result=f1/(f2*f3);
		printf ("%d = %d / (%d * %d)\n", result, f1, f2, f3);
	}
    printf("\n");
    getchar();
}
