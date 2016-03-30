#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //well sqrt() and abs() are used more times so yeah
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

typedef struct PtrLinkedList{
    void * data;
    float type;
    struct PtrLinkedList * next;
} APList;
/*
APList * createAPList(APList * list, void * data, int type){
	//printf("in createlist\n");
    list = (APList*) malloc(sizeof(APList));
	list->data = data;
    list->type = type;
	list->next = NULL;
	return list;
}
*/
APList * addAPNode(APList * list, void * data, int type){
	APList * node = (APList*) malloc(sizeof(APList));
	node->data = data;
    node->type = type;
	node->next = list;
	return node;
}

//used in CP19 and CP20
//sort list (bubble)
APList * sortAPList(APList * list, int order){ //1: increase, 0: decrease
    APList * ptr = list;
    APList * tmp = NULL;
    APList * ptr2 = list; //handles the pointer to the new node
    int isSwap = 1;
    while(isSwap){
        isSwap = 0;
        //printf("loop start\n");
        ptr = list; //ptr and ptr->next will swap
        ptr2 = list; //handles the pointer to the new node

        //One sweep
        while(ptr){
            if(ptr->next){
                if(ptr == ptr2){ //start of the list
                    if(order){
                        if(ptr->type > ptr->next->type){
                            list = ptr2->next;
                            tmp = ptr->next->next;
                            ptr->next->next = ptr;
                            ptr->next = tmp;
                            //printf("Tmp : %d\n", tmp->data);
                            isSwap = 1;
                            ptr2 = list;
                        } else {
                            ptr = ptr->next;
                        }
                    } else {
                        if(ptr->type < ptr->next->type){
                            list = ptr2->next;
                            tmp = ptr->next->next;
                            ptr->next->next = ptr;
                            ptr->next = tmp;
                            //printf("Tmp : %d\n", tmp->data);
                            isSwap = 1;
                            ptr2 = list;
                        } else {
                            ptr = ptr->next;
                        }
                    }
                } else { //ptr2 -> ptr
                    if(order){
                        if(ptr->type > ptr->next->type){
                            ptr2->next = ptr->next;
                            tmp = ptr->next->next;
                            ptr->next->next = ptr;
                            ptr->next = tmp;
                            //printf("Tmp : %d\n", tmp ? tmp->data : 0);
                            isSwap = 1;
                            //printf("before ptr2->next\n");
                            ptr2 = ptr2->next;
                        } else {
                            ptr2 = ptr;
                            ptr = ptr->next;
                        }
                    } else {
                        if(ptr->type < ptr->next->type){
                            ptr2->next = ptr->next;
                            tmp = ptr->next->next;
                            ptr->next->next = ptr;
                            ptr->next = tmp;
                            //printf("Tmp : %d\n", tmp ? tmp->data : 0);
                            isSwap = 1;
                            //printf("before ptr2->next\n");
                            ptr2 = ptr2->next;
                        } else {
                            ptr2 = ptr;
                            ptr = ptr->next;
                        }
                    }
                }
                //printf("before viewlist\n");
                //viewWordList(list);
            } else {
                break;
            }
        }
        //printf("\n");
    }
    return list;
}

/*
    *****************************************************************************
    ** ALL-PURPOSE FUNCTIONS / STRUCTURES ***************************************
    ** Functions / structures which may be used by a lot of other subprograms. **
    *****************************************************************************
*/

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

/*
    ********************************************************************
    ** PROGRAM FUNCTIONS ***********************************************
    ** The 20 subprograms, along with extra functions related to them **
    ********************************************************************
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program1(){
    printf("\nProgram 1: Trailing Zeros\n");
    int num;
    int zeros=0;
    printf ("Enter number: ");
    scanf ("%d", &num);
    while (num>0){
        num=num/5; // divide num by 5 and add quotient to 'zeros' //
        zeros+=num;
    }

    if (zeros>0){
        printf ("Number of trailing zeros: %d \n", zeros);
    }
    else printf ("There are no trailing zeros. \n");
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program2(){
    /*Finding segment intersection using vector cross products
    - express as segments from p (x,y) to p+r (x,y)+(plusx+plusy)
    */
    printf("\nProgram 2: Intersecting Segments\n");
    int ndx;
    float x[2], y[2], plusx[2], plusy[2];
    char input[100], *token;
    printf("Enter the 4 coordinates: ");
    fgets(input, 100, stdin);

    token = strtok(input, ", ");
    for(ndx=0; ndx<2; ndx++){
        x[ndx] = atof(token);
        token = strtok(NULL, ", ");
        y[ndx] = atof(token);
        token = strtok(NULL, ", ");
        plusx[ndx] = atof(token) - x[ndx];
        token = strtok(NULL, ", ");
        plusy[ndx] = atof(token) - y[ndx];
        token = strtok(NULL, ", ");
    }

    float t, u, den, qmpx, qmpy;
    qmpx = x[1]-x[0];
    qmpy = y[1]-y[0];
    den = plusx[0]*plusy[1] - plusx[1]*plusy[0]; //scalar = r x s
    if(den){
        t = (qmpx*plusy[1] - qmpy*plusx[1]) / den; //scalar t = (q - p) x s / r x s
        u = (qmpx*plusy[0] - qmpy*plusx[0]) / den; //scalar u = (q - p) x r / r x s
        if(t>=0 && t<=1 && u>=0 && u<=1){
            //intersect, meet at point
            printf("Segments intersect at (%.2f, %.2f)\n", x[0]+(plusx[0]*t), y[0]+(plusy[0]*t));
        } else {
            //do not intersect
            printf("NO INTERSECTION\n");
        }
    } else {
        if(qmpx*plusy[0] - qmpy*plusx[0]){
            //parallel, nonintersecting
            printf("NO INTERSECTION\n");
        } else {
            //collinear, may overlap
            float rdotr = plusx[0]*plusx[0] + plusy[0]*plusy[0];
            float t0 = (qmpx*plusx[0] + qmpy*plusy[0]) / rdotr;
            float sdotr = plusx[1]*plusx[0] + plusy[1]*plusy[0];
            float t1 = t0 + (sdotr / rdotr);
            if(sdotr < 0){ //swap t0 and t1. Source: http://www.geeksforgeeks.org/swap-two-numbers-without-using-temporary-variable/
                t0 += t1;
                t1 = t0 - t1;
                t0 = t0 - t1;
            }
            if((t0<=0 && t1>0) || (t0<1 && t1>=1) || (t0>=0 && t1<=1)){ //i have no idea what form of witchcraft makes this work but oh well
                printf("Segments overlap\n");
            } else if(t0==1){
                printf("Segments intersect at (%.2f, %.2f)\n", x[0]+plusx[0], y[0]+plusy[0]);
            } else if(t1==0){
                printf("Segments intersect at (%.2f, %.2f)\n", x[0], y[0]);
            } else {
                printf("NO INTERSECTION\n");
            }
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program3(){
    printf("\nProgram 3: Prime Factorization\n");
	int num, prime=2, count=0;

	printf ("Enter number: ");
	scanf ("%d", &num);



	printf ("The prime factor(s) is/are: \n");

	if (num==1)
	    printf ("1 \n");

	else
	{

	do
	    {
		    if (num%prime!=0)
		    {
			    prime+=1;
		    }

		    else
		    {
				count=1;
			    num/=prime;
			    printf("%d", prime);



			    while (num%prime==0)
			    {
			    	count++;
			    	num/=prime;

			    }

			    if (count>1)
			    {
				    printf ("^%d", count);
			    }

			    if (num==1)
			        {break;}

			printf (", ");

		    }



	    } while (num!=1);

	    printf ("\n");
	}
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program4(){
    //DONE
    printf("\nProgram 4: Subsets\n");
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    int set[n], bin[n];
    //set values
    int x;
    for(x=0; x<n; x++){
        set[x] = x+1;
        bin[x] = 0;
    }

    //print Subsets
    int y, * digit, comma, max = powInt(2,n);
    for(x=0; x<max; x++){
        printf("%s%s{", x ? "," : "", x ? (x+1)%5==0 ? "\n" : " " : "");
        //print subset
        comma = 0;
        for(y=0; y<n; y++){
            //print subset
            if(bin[y]){
                printf("%s%d", comma ? "," : "", set[y]);
                comma = 1;
            }
        }
        printf("}");

        //increment bin
        y = x+1;
        if(y == max) break;
        digit = bin;
        while(y){
            *digit = y%2;
            digit++;
            y /= 2;
        }
    }
    printf("\n");
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program5(){
    printf("\nProgram 5: Multiplying Polynomials\n");
    char input[IOLONG];
    char str[IOLONG];
    char * presentpoly;
    int firstpoly[IOLONG];
    int firstpolycount;
    int secondpoly[IOLONG];
    int secondpolycount;
    int finalpoly[IOLONG];

    int commas=0;

    printf("Enter first polynomial: ");
	fgets(input, IOLONG, stdin);

    if (input[strlen(input)-1] == 10)
		{
			input[strlen(input)-1] = 0;
		}


    strcpy(str,input);

    commas=0;
    firstpolycount = 0;
    presentpoly = strtok(str,",");
    //firstpolycount++;

    while(presentpoly)
    {
        //printf("\n%s",presentpoly);
        if(presentpoly!= NULL){
        sscanf(presentpoly,"%d",&firstpoly[firstpolycount]);
        firstpolycount++;}


        presentpoly = strtok(NULL,",");
    }

    int i;
    for(i=0;i<firstpolycount;i++)
    {
        //printf("\n%s",firstpoly[i]);
        //comment out entire loop later
    }

    /* second run  */


     printf("\nEnter second polynomial: ");
     //strcpy(input,"1,3");
	fgets(input, IOLONG, stdin);

    if (input[strlen(input)-1] == 10)
		{
			input[strlen(input)-1] = 0;
		}


    strcpy(str,input);

    commas=0;
    secondpolycount = 0;
    presentpoly = strtok(str,",");


    while(presentpoly)
    {
        //printf("\n%s",presentpoly);
        if(presentpoly!= NULL){
        sscanf(presentpoly,"%d",&secondpoly[secondpolycount]);
        secondpolycount++;}


        presentpoly = strtok(NULL,",");
    }

    for(i=0;i<secondpolycount;i++)
    {
        //printf("\n%s",secondpoly[i]);
        //comment out entire loop later
    }


    for (i=0;i<secondpolycount+firstpolycount-1;i++)
    {
        finalpoly[i]=0;
    }

    int j;
    for (i=firstpolycount-1;i>=0;i--)
    {
        for(j=secondpolycount-1;j>=0;j--)
        {
        //printf("\n[%d][%d] %d * %d = %d",finalpoly[(firstpolycount-1-i)+(secondpolycount-1-j)],(firstpolycount-1-i)+(secondpolycount-1-j),firstpoly[i],secondpoly[j], firstpoly[i]*secondpoly[j]);
        finalpoly[(firstpolycount-1-i)+(secondpolycount-1-j)]=(firstpoly[i] * secondpoly[j]) + finalpoly[(firstpolycount-1-i)+(secondpolycount-1-j)];

        }
    }

    printf("\nFINAL POLYNOMIAL:\n");
     for(j=secondpolycount+firstpolycount-2;j>=0;j--)
        {

        printf("%d",finalpoly[j]);

        if (j!=0)
        {
            printf (",");
        }

        }
    printf("\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program6(){
    //DONE
    printf("\nProgram 6: Mabu's Corridor\n");
    int n, i, bulb = 1;
    char input_string[IOSHORT];

    do{
        printf("How many times does Mabu walk back and forth? ");
        fgets(input_string, IOSHORT, stdin);
        n = atoi(input_string);
        if(n < 0){
            printf("That can't be negative. Try again.\n");
            continue;
        }
        break;
    }while(1);

    for(i=1; i<=n; i++)
        if(n%i==0) bulb = !bulb;
    printf("The last bulb is %s\n", bulb ? "on." : "off.");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program7(){
    printf("\nProgram 7: Fractions Less Than 1\n");
    int num, a, b, check, ctr;

    printf ("Enter n: ");
    scanf ("%d", &num);

    b=num;

    for (a=1;a<b;a++)
    {
        ctr=2;
        check=0;

        while(ctr!=b)
        {
            if (a%ctr==0 && b%ctr==0)
            {
                check=1;
                break;
            }

            ctr+=1;
        }

        if (check==0)
        {
            printf ("%d/%d ", a, b);
            //printf (", ");
        }
    }
    printf("\n");
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program8(){
    printf("\nProgram 8: Distance Between 2 Points\n");
    char * xinput = (char*) malloc(sizeof(char)*IOLONG);
    printf("Enter a list of x coordinates: ");
    fgets(xinput, IOLONG, stdin);
    char * yinput = (char*) malloc(sizeof(char)*IOLONG);
    printf("Enter a list of y coordinates: ");
    fgets(yinput, IOLONG, stdin);

    int xlen, ylen;
    float * xs;
    xs = processInputFloat(xinput, xs, &xlen);
    float * ys;
    ys = processInputFloat(yinput, ys, &ylen);
    //xlen and ylen HAVE to be the same

    //Start comparing distances
    if(xlen <= 1){
        printf("2 or more points required.\n");
    } else {
        float x1, x2, y1, y2;
        float d_max = FLT_MAX;
        float d_curr;
        int p1, p2;
        for(p1=0; p1<xlen; p1++){
            for(p2=p1; p2<xlen; p2++){
                d_curr = distance(*(xs+p1), *(xs+p2), *(ys+p1), *(ys+p2));
                if(d_curr && d_curr < d_max){
                     d_max = d_curr;
                     x1 = *(xs+p1);
                     x2 = *(xs+p2);
                     y1 = *(ys+p1);
                     y2 = *(ys+p2);
                }
            }
        }
        printf("The points (%.2f, %.2f) and (%.2f, %.2f) are the nearest.\n", x1, y1, x2, y2);
    }
    free(xinput);
    free(yinput);
    free(xs);
    free(ys);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

unsigned long long int fact (int n)
{
	unsigned long long int ans=1;
	int x=1;

	for (x=1;x<=n;x++)
	ans=ans*x;

	return ans;
}

void program9(){
    printf("\nProgram 9: Pascal's Triangle");
    int n, b;
    unsigned long long int f1, f2, f3, result;
	printf("\nEnter nth line: ");
	scanf("%d", &n);
	for (b=0;b<=n;b++)
	{
        f1 = fact(n);
        f2 = fact(b);
        f3 = fact(n-b);
		result=f1/(f2*f3);
		printf ("%s%lld", b ? ", " : "", result);
	}
    printf("\n");
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program10(){
    //DONE, Tested ?
    printf("\nProgram 10: Roman Numerals\n");
    int n;
    printf("Enter a number from 0 to 1000: ");
    scanf("%d", &n);
    char output[15];
    int ndx = 0, place = 0, placeVal = 0; //0-ones, 1-tens, sosf;
    int numpow = 1;
    while(numpow*10 <= n){
        numpow*=10;
        place++;
    }
    while(n){
        placeVal = n / numpow;
        if((placeVal+1) % 5 == 0){
            output[ndx] = place ? place==2 ? 'C' : 'X' : 'I';
            ndx++;
            if(placeVal==9){
                output[ndx] = place ? place==2 ? 'M' : 'C' : 'X';
                ndx++;
            } else {
                output[ndx] = place ? place==2 ? 'D' : 'L' : 'V';
                ndx++;
            }
        } else {
            if(placeVal >= 5){
                output[ndx] = place ? place==2 ? 'D' : 'L' : 'V';
                ndx++;
                placeVal -= 5;
            }
            while(placeVal){
                output[ndx] = place ? (place>=2 ? (place==3 ? 'M' : 'C') : 'X') : 'I';
                ndx++;
                placeVal--;
            }
        }
        n %= numpow;
        numpow /= 10;
        place--;
    }
    output[ndx] = '\0';
    printf("%s\n", output);
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program11(){
    float input, frac;
    int temp, numer, ctr, x=1, denom=1000000;;

    printf ("Enter n: ");
    scanf ("%f", &input);

    while (input > 0.0000001)
    {
    	frac = 1/ (float) x;

        if (frac - input > 0.00000001)
        {
            x++;
        }

        else
        {
            input-=frac;
    		printf("1/%d = %.4f\n", x, frac);
            printf ("FRAC: %f\n", frac);
            printf("INPT: %f\n\n", input);
            x++;
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program12(){
    //DONE
    float denominations[] = {1000, 500, 200, 100, 50, 20, 10, 5, 1, 0.25, 0.1, 0.05};
    float input;
    printf("\nProgram 12: Peso Denominations\n");
    printf("Enter a peso amount: ");
    scanf("%f", &input);
    int isFirst = 1, ndx = 0;
    while(input - 0.05 > 0.000001){
        if((int) (input / denominations[ndx])){
            if(ndx < 9){
                printf("%s(%d) %.0f", isFirst ? "" : " + ", (int) (input / denominations[ndx]), denominations[ndx]);
            } else {
                printf("%s(%d) %.2f", isFirst ? "" : " + ", (int) (input / denominations[ndx]), denominations[ndx]);
            }
            isFirst=0;
        }
        input -= ((int) (input / denominations[ndx]))*denominations[ndx];
        ndx++;
    }
    printf("\n");
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program13(){
    printf("\nProgram 13: Add Numbers\n");
    printf("Enter first number: ");
    char num1[IOMED];
    fgets(num1, IOMED, stdin);
    printf("Enter second number: ");
    char num2[IOMED];
    fgets(num2, IOMED, stdin);
    APList * lnum1 = NULL, * lnum2 = NULL, *ladd = NULL;
    int ndx;
    for(ndx = 0; num1[ndx]!='\n'; ndx++){
        lnum1 = addAPNode(lnum1, NULL, num1[ndx] - (int)'0');
    }
    for(ndx = 0; num2[ndx]!='\n'; ndx++){
        lnum2 = addAPNode(lnum2, NULL, num2[ndx] - (int)'0');
    }

    APList * ptr1 = lnum1, * ptr2 = lnum2;
    int carry = 0;
    while(ptr1 || ptr2 || carry){
        ladd = addAPNode(ladd, NULL, 0);
        if(ptr1){
            ladd->type += ptr1->type;
            ptr1 = ptr1->next;
        }
        if(ptr2){
            ladd->type += ptr2->type;
            ptr2 = ptr2->next;
        }
        ladd->type += carry;
        carry = (int) (ladd->type) / 10;
        ladd->type = (int) (ladd->type) % 10;
    }

    ptr1 = ladd;
    while(ptr1){
        printf("%.0f", ptr1->type);
        ptr1 = ptr1->next;
        free(ladd);
        ladd = ptr1;
    }
    printf("\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program14(){
    //DONE
    printf("\nProgram 14: Base Converter\n");
    int n, b;
    printf("Enter a number to convert: ");
    scanf("%d", &n);

    do{
        printf("Enter a base to convert to (max 36): ");
        getchar();
        scanf("%d", &b);
        if(b == 1){
            printf("A base1 number of a base10 \'n\' is simply a list of \'n\' characters. Try again.\n");
        } else if(b < 1){
            printf("A base has to be positive. Try again.\n");
        } else if(b > 36){
            printf("Please limit to 36. Try again.\n");
        }
    }while(b <= 1 || b > 36);
    printf("%d at base %d = %s", n, b, n<0 ? "-" : "");
    if(n<0) n *= -1;

    int place = b, ans = 0;
    while(place < n) place *= b;
    place /= b;
    while(place > 0){
        if(n / place < 10){
            printf("%d", n / place);
        } else {
            printf("%c", (n / place) - 10 + (int)'A');
        }
        n %= place;
        place /= b;
    }
    printf("\n");
    getchar();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program15(){
    printf("\nProgram 15: Sorting\n");
    printf("Enter a list of numbers: ");
    char string[IOMED];
    fgets(string, IOMED, stdin);
    char * token = strtok(string, " ,");
    //using APList node; numbers will be stored in ptr->type
    APList * list = NULL;
    while(token){
        printf("%s\n", token);
        list = addAPNode(list, NULL, atoi(token));
        token = strtok(NULL, " ,");
    }

    APList * ptr = list;
    APList * tmp = NULL;
    APList * ptr2 = list; //handles the pointer to the new node
    int isSwap = 1;
    while(isSwap){
        isSwap = 0;
        //printf("loop start\n");
        ptr = list; //ptr and ptr->next will swap
        ptr2 = list; //handles the pointer to the new node

        //One sweep
        while(ptr){
            if(ptr->next){
                if(ptr == ptr2){ //start of the list
                    if(ptr->type > ptr->next->type){
                        list = ptr2->next;
                        tmp = ptr->next->next;
                        ptr->next->next = ptr;
                        ptr->next = tmp;
                        isSwap = 1;
                        ptr2 = list;
                    } else {
                        ptr = ptr->next;
                    }
                } else { //ptr2 -> ptr
                    if(ptr->type > ptr->next->type){
                        ptr2->next = ptr->next;
                        tmp = ptr->next->next;
                        ptr->next->next = ptr;
                        ptr->next = tmp;
                        isSwap = 1;
                        ptr2 = ptr2->next;
                    } else {
                        ptr2 = ptr;
                        ptr = ptr->next;
                    }
                }
            } else {
                break;
            }
        }
    }

    ptr = list;
    while(ptr){
        printf("%.0f%s", ptr->type, ptr->next ? ", " : "");
        ptr = ptr->next;
        free(list);
        list = ptr;
    }
    printf("\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct circle{
    float x;
    float y;
    float r;
} Circle;

void program16(){
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
    Circle set[50];
    int setn = 0, ndx = 0;
    char * token = NULL;

    //set x values
    token = strtok(xinput, " ,");
    while(token){
        set[setn].x = atof(token);
        setn++;
        token = strtok(NULL, " ,");
    }
    //set y values
    token = strtok(yinput, " ,");
    while(token){
        set[ndx].y = atof(token);
        ndx++;
        token = strtok(NULL, " ,");
    }
    //set r values
    ndx = 0;
    token = strtok(radinput, " ,");
    while(token){
        set[ndx].r = atof(token);
        ndx++;
        token = strtok(NULL, " ,");
    }

    //print values
    for(ndx=0;ndx<setn;ndx++){
        printf("C(%.2f,%.2f) w/ radius %.2f\n", set[ndx].x, set[ndx].y, set[ndx].r);
    }

    int inters[setn];
    float circdist;
    //set inters to all 0
    for(ndx=0;ndx<setn;ndx++) inters[ndx] = 0;
    int ndx2 = 0;
    Circle tmp;
    for(ndx=0;ndx<setn-1;ndx++){
        for(ndx2=ndx+1;ndx2<setn;ndx2++){
            //detect number of intersections
            //congruent?
            //they overlap? r1 >= dist(c1,c2) - r2
            circdist = distance(set[ndx].x, set[ndx2].x, set[ndx].y, set[ndx2].y);
            if(fabs(set[ndx].r - (circdist - set[ndx2].r)) < 0.000001){
                //tangent outside
                inters[ndx]++;
                inters[ndx2]++;
            } else if(set[ndx].r > (circdist - set[ndx2].r)){
                //they inside one another? r1 > dist(c1,c2) + r2
                //this only works if r1 >= r2
                if(max(set[ndx].r, set[ndx2].r) < (circdist + min(set[ndx].r, set[ndx2].r))){
                    //2 intersections
                    inters[ndx]+=2;
                    inters[ndx2]+=2;
                } else if(fabs(max(set[ndx].r, set[ndx2].r) - (circdist + min(set[ndx].r, set[ndx2].r))) < 0.000001){
                    //tangent inside
                    inters[ndx]++;
                    inters[ndx2]++;
                }
            }
            //printf("Circ %d & %d (%.2f): %d, %d\n", ndx, ndx2, circdist, inters[ndx], inters[ndx2]);
        }
    }

    //get biggest values

    int maxinter = 0;
    for(ndx=0;ndx<setn;ndx++){
        printf("%d ", inters[ndx]);
        if(maxinter < inters[ndx]) maxinter = inters[ndx];
    }
    printf("\n");
    for(ndx=0;ndx<setn;ndx++){
        if(maxinter == inters[ndx]){
            printf("%.0f, %.0f, %.0f\n", set[ndx].x, set[ndx].y, set[ndx].r);
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program17(){
    //Source of algorithm: https://dspace.mit.edu/bitstream/handle/1721.1/4015/HPCES024.pdf?sequence=2
    //Randomized incremental algorithm
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program18(){
    //DONE, CHECK, FORMAT
    printf("\nProgram 18: Texting\n");
    char * string = (char*) malloc(sizeof(char)*IOLONG);
    printf("Enter string: ");
    fgets(string, IOLONG, stdin);
    int freq = 0, num = 0, val = 0;
    char * ptr = string;
    while(*ptr != '\n'){
        *ptr = tolower(*ptr);
        ptr++;
    }
    ptr = string;
    for(;*ptr != '\n';ptr++){
        val = *ptr - (int) 'a';
        num = (val/3) + 2;
        freq = (val%3) + 1;
        if(num > 9){ //y, z
            num = 9;
            if(freq == 1){ //y
                freq = 3;
            } else if(freq == 2){ //z
                freq = 4;
            }
        } else if(num > 7){ //shift by one
            freq--;
            if(!freq){
                num--;
                freq = num%2==1 ? 4 : 3;
            }
        } else if(num == -19){ // space
            num = 0;
            freq = 1;
        }
        for(;freq>0; freq--){
            printf("%d", num);
        }
    }
    printf("\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct TimeBlock{
    float lower;
    float upper;
} TimeBlock;

void program19(){
    printf("\nProgram 19: Scheduling\n");
    printf("Please enter a series of time blocks: \n");
    char string[IOLONG];
    fgets(string, IOLONG, stdin);
    //strcpy(string, "8:30a-10a, 1130a-1p, 2:30p  -  4:00p");
    char * token;
    APList * list = NULL;
    token = strtok(string, " ,:-\n");
    int tok_int = 0, cycle = 0; //cycle: h-up -> min-up -> h-lw -> sosf.
    float hrmin = 0;
    while(token){
        //printf("%s\n", token);
        //parse token into a TimeBlock
        //data holds TimeBlock *; type holds lower bound
        if(cycle%4 == 0){
            list = addAPNode(list, NULL, 0);
            list->data = malloc(sizeof(TimeBlock));
            ((TimeBlock*) (list->data))->lower = 0;
            ((TimeBlock*) (list->data))->upper = 0;
        }
        tok_int = atoi(token);
        token+=strlen(token)-1;
        if(*token == 'a' || *token == 'p'){ //set the upper / lower
            if(tok_int < 60){ //minutes only or hours only w/ a/p
                if(cycle%2 == 0){ //hours only w/ a/p
                    hrmin += tok_int*100;
                    cycle+=2;
                } else { //minutes only
                    hrmin += tok_int;
                    cycle++;
                }
            } else { //hourminute a/p
                hrmin = tok_int;
                cycle+=2;
            }

            if(*token == 'p' && hrmin/100 != 12) hrmin += 1200;

            if(cycle%4 == 0){
                ((TimeBlock*) (list->data))->upper = hrmin/100;
                hrmin = 0;
            } else if(cycle%4 == 2){
                ((TimeBlock*) (list->data))->lower = hrmin/100;
                list->type = hrmin/100;
                hrmin = 0;
            }
        } else { //hours only
            hrmin += tok_int*100;
            cycle++;
        }
        //8:30a - 10:00a, 11:30a - 1:00p, 2:30p - 4:00p
        //printf(":%.2f:%c:\n~%d~\n\n", hrmin, *token, cycle);
        token = strtok(NULL, " ,:-\n");
    }

    list = sortAPList(list, 1);
    APList * ptr = list;
    //get the free times
    ptr = list;
    TimeBlock freetime;
    freetime.lower = 8.00;
    freetime.upper = 20.00;
    int noBreaks = 1;
    int hr, min;

    while(ptr){
        freetime.upper = ((TimeBlock*) (ptr->data))->lower;
        if(freetime.lower < freetime.upper){
            noBreaks = 0;
            hr = (int)freetime.lower%12;
            min = (int)(freetime.lower*100) % 100;
            printf("%d:%s%d%s-", hr, min<10?"0":"", min, freetime.lower >= 12 ? "PM" : "AM");
            freetime.lower = ((TimeBlock*) (ptr->data))->upper;

            hr = (int)freetime.upper%12;
            min = (int)(freetime.upper*100) % 100;
            printf("%d:%s%d%s%s", hr, min<10?"0":"", min,
                freetime.upper >= 12 ? "PM" : "AM", freetime.lower<20?", ":"");
        }
        ptr = ptr->next;
    }
    freetime.upper = 20.00;
    if(freetime.lower < freetime.upper){
        noBreaks = 0;
        hr = (int)freetime.lower%12;
        min = (int)(freetime.lower*100) % 100;
        printf("%d:%s%d%s-", hr, min<10?"0":"", min, freetime.lower >= 12 ? "PM" : "AM");
        hr = (int)freetime.upper%12;
        min = (int)(freetime.upper*100) % 100;
        printf("%d:%s%d%s", hr, min<10?"0":"", min, freetime.upper >= 12 ? "PM" : "AM");
    }

    if(noBreaks){
        printf("No breaks :'(");
    }
    printf("\n");

    //free list
    ptr = list;
    while(ptr){
        ptr = ptr->next;
        free(list->data);
        free(list);
        list = ptr;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void program20(){
    //DONE, CHECK, FORMAT
    printf("\nProgram 20: Word Frequency\n");
    /*
    typedef struct LinkedList20{
        char * string;
        int data;
        struct LinkedList20 * next;
    } WordList;
    */
    APList * list = NULL;
    char * string = (char*) malloc(sizeof(char)*IOLONG);
    printf("Enter a string of words separated by a space:\n");
    fgets(string, IOLONG, stdin);
    trim(string);
    //printf("After trim\n");

    //process input
    char del = ' ';
    char * token = strtok(string, &del);
    APList * ptr = NULL;
    while(token){
        //add to the list
        ptr = list;
        while(ptr){
            if(strcmp((char*)ptr->data, token) == 0){
                (ptr->type)++;
                break;
            } else {
                ptr = ptr->next;
            }
        }
        if(!ptr){
            ptr = (APList*) malloc(sizeof(APList));
            //This next part is experimental
            ptr->data = malloc(sizeof(char)*IOMED);
            strcpy((char*) ptr->data, token);
            //This ends the experimental part
            //ptr->data = token;
            ptr->type = 1;
            ptr->next = list;
            list = ptr;
        }
        token = strtok(NULL, &del);
    }

    list = sortAPList(list, 0);

    //print list
    ptr = list;
    while(ptr){
        printf("%s (%.0f)\n", (char*) ptr->data, ptr->type);
        ptr = ptr->next;
    }

    //free list
    ptr = list;
    while(list){
        ptr = ptr->next;
        free(list->data);
        free(list);
        list = ptr;
    }
}

/*
    **************************************
    ** MAIN FUNCTION *********************
    ** Contains the program picker loop **
    **************************************
*/

int main(){
    int program_num = 0;
    char * input_string = (char*) malloc(sizeof(char) * IOSHORT);
    do{
        printf("Please enter a program to test: ");
        fgets(input_string, IOSHORT, stdin);
        program_num = atoi(input_string);

        switch(program_num){
            case 1: program1(); break;
            case 2: program2(); break;
            case 3: program3(); break;
            case 4: program4(); break;
            case 5: program5(); break;
            case 6: program6(); break;
            case 7: program7(); break;
            case 8: program8(); break;
            case 9: program9(); break;
            case 10: program10(); break;
            case 11: program11(); break;
            case 12: program12(); break;
            case 13: program13(); break;
            case 14: program14(); break;
            case 15: program15(); break;
            case 16: program16(); break;
            case 17: program17(); break;
            case 18: program18(); break;
            case 19: program19(); break;
            case 20: program20(); break;
            default: printf("Bye bye!\n"); break;
        }
    }while(program_num > 0 && program_num < 21);
}
