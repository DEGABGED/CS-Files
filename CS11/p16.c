#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define IOSHORT 20 //for integers
#define IOMED 100 //for long integers and others
#define IOLONG 200
#define FLT_MAX 1E+37 //dont wanna import float.h just for a macro

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

typedef struct circle{
    float x;
    float y;
    float r;
    struct circle * next;
} Circle;

Circle * addCircle(Circle * list ,float x, float y, float r){
	//printf("in addnode\n");
    if(!list){
        list = (Circle*) malloc(sizeof(Circle));
    	list->x = x;
    	list->y = y;
    	list->r = r;
    	list->next = NULL;
    	return list;
    } else {
        Circle * node = list;
        while(node->next) node = node->next;
    	node->next = (Circle*) malloc(sizeof(Circle));
        node = node->next;
    	node->x = x;
    	node->y = y;
    	node->r = r;
    	node->next = NULL;
    	return list;
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

//Copied from my (Francis) MP1
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

float max(float a, float b){
    return a > b ? a : b;
}

int circleInside(Circle * ci, Circle * d){
    if(!d) return 0;
    return 1;
}

void circleLine(float m, float b, float x, float y, float r, float * x1, float * x2, float * y1, float * y2){
    float a = m + 1;
    float b = 2*x + 2*m*b + 2*y*m;
    float c = x*x + b*b + 2*y*m*b + y*y - r*r;
    float out = b*b - 4*a*c;
    out = sqrt(out);
    *x1 = ((-1*b) - out) / (2*a);
    *x2 = ((-1*b) + out) / (2*a);
    *y1 = m*(*x1) + b;
    *y2 = m*(*x2) + b;
}

void solveForCircle(Circle * b, Circle * d){
    if(b){
        if(b->next){
            if(b->next->next){ //3+

            } else { //2
                //1: get the mdpt c1-c2
                float del_y = (b->y - b->next->y);
                float del_x = (b->x - b->next->x);
                float xinter1[4], yinter1[4], xinter2[4], yinter2[4];
                if(!del_x){

                } else {
                    float m = del_y / del_x;
                    float yroot = b->y - (m * (b->x));
                    circleLine(m, yroot, b->x, b->y, b->r, xinter, xinter+1, yinter, yinter+1);
                    circleLine(m, yroot, b->next->x, b->next->y, b->next->r, xinter+2, xinter+3, yinter+2, yinter+3);

                }
            }
        }
    }
}

//c: Circle - set of circle addresses
//b: Circle - set of circle addresses
//ci: Circle - single circle address
//d: Circle * - holds the output
Circle * recCircle(Circle * c, Circle * b, Circle * d){
    if(!c){
        if(!b){
            return NULL;
        } else if(!(b->next)){
            return b;
        } else if(!(b->next->next)){
            //compute smallest circle w/ 2 circles
            if(!d) d = (Circle*) malloc(sizeof(Circle*));
            solveForCircle(b, d);
        }
    } else {
        Circle * ci = c;
        c = c->next;
        d = recCircle(c, b, d);
        if(circleInside(ci, d)){
            if(!b){
                ci->next = b;
                b = ci;
                d = recCircle(c, b, d);
            } else if(!(b->next)){
                ci->next = b;
                b = ci;
                d = recCircle(c, b, d);
            } else {
                //do the fucking thing
                if(!d) d = (Circle*) malloc(sizeof(Circle*));
                solveForCircle(b, d);
            }
        }
    }
    return d;
}

int main(){
    printf("\nProgram 16: Circle with most Intersections\n");
    char xinput[IOLONG];
    char yinput[IOLONG];
    char radinput[IOLONG];
    printf("Enter the x values: ");
    fgets(xinput, IOLONG, stdin);
    printf("Enter the y values: ");
    fgets(yinput, IOLONG, stdin);
    printf("Enter the radii: ");
    fgets(radinput, IOLONG, stdin);
    Circle * set = NULL;
    int setn = 0;
    char * token = NULL;

    //set x values
    token = strtok(xinput, " ,");
    while(token){
        set = addCircle(set, atof(token), 0, 0);
        setn++;
        token = strtok(NULL, " ,");
    }
    //set y values
    Circle * ptr = set;
    token = strtok(yinput, " ,");
    while(token){
        ptr->y = atof(token);
        ptr = ptr->next;
        token = strtok(NULL, " ,");
    }
    //set r values
    token = strtok(radinput, " ,");
    ptr = set;
    while(token){
        ptr->r = atof(token);
        ptr = ptr->next;
        token = strtok(NULL, " ,");
    }

    //print values
    for(ptr=set;ptr;ptr=ptr->next){
        printf("C(%.2f,%.2f) w/ radius %.2f\n", ptr->x, ptr->y, ptr->r);
    }

    Circle * out = NULL;
}
