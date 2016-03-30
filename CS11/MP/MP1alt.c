#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define HD_MAX_DIGITS 5 //arbitrarily defined :P

/*
	**********************************
	** ARRAY PRINTERS: FOR CHECKING **
	**********************************
*/
/*Prints Integer Array*/
void printIntArray(int c[], int c_len){
	printf("***PRINTING***\n");
	int ctr = 0;
	for(; ctr<c_len; ctr++){
		printf("%d\n", c[ctr]);
	}
	printf("***FINISHED***\n\n");
}

/*Prints Float Array*/
void printFloatArray(float c[], int c_len){
	printf("***PRINTING***\n");
	int ctr = 0;
	for(; ctr<c_len; ctr++){
		printf("%.3f\n", c[ctr]);
	}
	printf("***FINISHED***\n\n");
}

/*
	**************************
	** SIMPLE ARRAY EDITORS **
	**************************
*/
/*Removes whitespaces
Used before input validation*/
void trim(char string[]){
	//printf("\n***BEFORE TRIM:%s:***", string);
	int ndx_s = 0; //start of string
	int ndx_e = strlen(string) - 1; //end of string
	while(string[ndx_e] == ' ' || string[ndx_e] == '\t' || string[ndx_e] == '\n'){
		string[ndx_e] = '\0';
		ndx_e--;
	}
	ndx_e++;

	int ndx_s_out = 0; //start of string w/o whitespaces
	for(ndx_s = 0; ndx_s <= ndx_e; ndx_s++){
		if(string[ndx_s] == ' ' || string[ndx_s] == '\t' || string[ndx_s] == '\n'){
			ndx_s_out++;
		} else {
			break;
		}
	}

	//shifting
	if(ndx_s_out){
		for(ndx_s = 0; ndx_s + ndx_s_out <= ndx_e; ndx_s++){
			string[ndx_s] = string[ndx_s + ndx_s_out];
		}
	}
	//printf("\n***AFTER TRIM:%s:***\n", string);
}

/*Initiallizes float array values all to num
Used to set initial values for zeroes_n and zeroes_d*/
void fill(float a[], float num, int len){
	for(;len>=0;len--){
		a[len] = num;
	}
}

/*Initiallizes int array values all to num
Used to set initial values for zeroes*/
void fillInt(int a[], int num, int len){
	for(;len>=0;len--){
		a[len] = num;
	}
}

/*Swaps the values in 2 addresses
Used for the sortInt and gcf functions*/
void swap(int * a, int * b){
	static int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
/*Swaps the float values in 2 addresses
//Used for the sortFloat function
void swapFloat(float * a, float * b){
	static int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
*/

/*
	*********************************
	** CHECKERS: RETURNS "BOOLEAN" **
	*********************************
*/
/*Checks if char string is an integer. If so, int address gets the int value and function returns 1. If not, returns 0.
Used for two purposes: one for degree input, the other for coefficient input*/
int isNotNumber(char string[], int * number, int isDegree){
	//check if entire string is numbers
	trim(string);
	//printf("***\nstring[]: %s\n***\n\n", string);
	static const char allowed[] = "-1234567890";
	int ndx = 0;
	int len = strlen(string);
	for(;ndx < len; ndx++){
		if(strchr(allowed, string[ndx]) == NULL){
			printf("Error: Input not a number. Try again.\n");
			return 1;
		}
	}

	if(strlen(string) > HD_MAX_DIGITS){
		printf("Warning: Integer too large. Try entering a smaller number.\n");
		return 1;
	}
	*number = atoi(string); //for some weird reason, entering "1a" here yields 1; "a1" doesn't. wtf c
	if(*number!=0){
		if(isDegree){
			if(*number < 0){
				printf("Error: Input is negative. Try again.\n");
			} else {
				return 0;
			}
		} else {
			return 0; //for coefficients, negative numbers are allowed
		}
	} else {
		if(isDegree){
			printf("Error: Input can't be 0. Try again.\n"); //Possible that 0 is allowed; but it's a special test case anyway
		} else {
			return 0; //for coefficients, 0 is a possible input
		}
	}
	return 1;
}

/*Searches float array for a num; outputs 1 if found; 0 if not
Used in finding out if a root has been found before to avoid repetition in the output.*/
int isHere(float a[], float num, int roots){
	int ndx = 0;
	for(;ndx<roots;ndx++){
		if(num == a[ndx]) return 1;
	}
	return 0;
}

/*
	*************
	** SORTING **
	*************
*/
/*
/*Sorts a float array (Bubble)
//Used initially for sorting the zeroes[] array, which proved to be pointless.
void sort(float a[], int len){
	int swapped = 1, ndx;
	len--;
	do{
		swapped = 0;
		for(ndx = 0; ndx < len; ndx++){
			if(a[ndx] > a[ndx+1]){
				swapFloat(&a[ndx], &a[ndx+1]);
				swapped = 1;
			}
		}
	}while(swapped);
}
*/

/*Sorts the output (2 arrays) (Bubble)
Used once to sort the fractional outputs*/
void sortND(int n[], int d[], int len){
	//printf("\n***************\n** IN SORTND **\n***************\n");
	int swapped = 1, ndx;
	len--;
	do{
		swapped = 0;
		//printIntArray(n, len+1);
		//printIntArray(d, len+1);
		for(ndx = 0; ndx < len; ndx++){
			if(((float)n[ndx] / d[ndx]) > ((float)n[ndx+1] / d[ndx+1])){
				swap(&n[ndx], &n[ndx+1]);
				swap(&d[ndx], &d[ndx+1]);
				swapped = 1;
			}
		}
	}while(swapped);
	//printIntArray(n, len+1);
	//printIntArray(d, len+1);
	//printf("\n***************\n** OUTSORTND **\n***************\n");
}

/*
	***********************
	** NUMBER PROCESSING **
	***********************
*/
/*Takes integer x and writes integer factors of x onto array
Used for finding factors of p and q.*/
void factor(int num, int factors[], int factors_l){
	//printf("In factor function\n");
	num = fabs(num);
	int mdpt = (int) sqrt(num);
	//printf("num:%d mdpt:%d\n", num, mdpt);
	int f = 1;
	int ctr = 0;
	for(; f<=mdpt; f++){
		if(num%f==0){
			factors[ctr] = f;
			ctr++;
			factors[ctr] = -f;
			ctr++;
			if((f != mdpt) || (f == 1)){
				factors[ctr] = num/f;
				ctr++;
				factors[ctr] = - num/f;
				ctr++;
			}
		}
	}

	for(; ctr<factors_l; ctr++){
		factors[ctr] = 0;
	}
}

/*Finds the greatest common factor between two numbers
Used for simplifying fractions; possibly useless.*/
int gcf(int n, int d){
	if(n < d) swap(&n, &d);
	int temp;
	while(n%d){
		temp = n;
		n = d;
		d = temp%d;
	}
	return d;
}

/*Takes input x and a polynomial's coefficients; outputs f(x)
Used for checking for roots (in contrast to the synthetic division method)*/
float polyfxn(int coeff[], int coeff_l, float x){
	int ctr = 0;
	float y = 0;
	for(; ctr<coeff_l; ctr++){
		y += (coeff[ctr] * pow(x, ctr));
	}
	return y;
}

/*
	*******************
	** MAIN FUNCTION **
	*******************
*/
int main(){
	/*
		***************
		** VARIABLES **
		***************
	*/
	char yn[10]; //INPUT string; holds a yes/no response
	int program_loop = 1; //if 0, program stops
	char high_deg[100]; //INPUT string; holds the highest degree directly from user
	char coeffs_list[6*100]; //INPUT string; holds the list of coefficients directly from user
	int hdnum; //INPUT: holds the higest degree (int)
	int loopvar = 1; //if 0, checking loops stop;
	char * coeff_s; //INPUT: string to hold each coefficient in the input string
	int coeffs_c; //INITIALIZED INSIDE: counter of the while loop
	do{
		loopvar = 1;
		/*
			**************************
			** HIGHEST DEGREE INPUT **
			**************************
		*/
		//loop to inputcheck first input
		while(loopvar){
			//high_deg[4] = '\0';
			printf("\nEnter the highest degree of the input polynomial: ");
			fgets(high_deg, 100, stdin);
			//if((high_deg[4]!='\0') && (high_deg[4]!='\n')) while(getchar() != '\n');
			if(strchr(high_deg, '.') != NULL){
				printf("Error: Degree must be an integer. Try again\n");
				continue;
			}
			loopvar = isNotNumber(high_deg, &hdnum, 1);
		}

		hdnum++;
		//printf("Number is %d\n", hdnum);
		int coeffs[hdnum]; //int array of coefficients

		/*
			************************
			** COEFFICIENTS INPUT **
			************************
		*/
		loopvar = 1; //reinitializes loopvar
		//loop to inputcheck second input
		int hdnum_o = hdnum; //for when an error with the degree occurs after changing it
		while(loopvar){
			//gets the numbers; code from http://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
			coeff_s = NULL;
			printf("\nEnter %d coefficients starting from the 0th degree.\nSeparate each input from a comma: ", hdnum);
			fgets(coeffs_list, 6*100, stdin);
			if(strchr(coeffs_list, '.') != NULL){
				printf("Error: Coefficients must be integers. Try again\n");
				continue;
			}

			//separates string into string with ',' as a delimiter
			coeff_s = strtok(coeffs_list, ",");
			coeffs_c = 0;
			while(coeffs_c < hdnum){
				if(coeff_s == NULL){
					printf("Error: Incomplete coefficients. Try again\n");
					break;
				} else {
					if(isNotNumber(coeff_s, &coeffs[coeffs_c], 0)){
						break;
					}
				}
				coeff_s = strtok(NULL, ",");
				coeffs_c++;
				if(coeffs_c >= hdnum){
					//at this part, the input getting is finished and validated, and the loop will end shortly.
					loopvar = 0;
					if(coeff_s != NULL){
						printf("Warning: More than what was asked for was entered. Program will accept only the first %d coefficients.\n", hdnum);
					}
					//checks if last coefficient is a zero
					//apparently you can help the user and consider the 0, and just change the degree
					/*
					if(coeffs[coeffs_c-1] == 0){
						printf("Error: coefficient of highest degree term can't be 0. Try again\n");
						loopvar = 1;
					}
					*/
					if(coeffs[hdnum-1] == 0){
						printf("Warning: The last coefficient/s is/are 0. Program will change the degree of the entire polynomial accordingly.\n");
						while(coeffs[hdnum-1] == 0){
							hdnum--;
						}
					}
					if(hdnum <= 1){
						printf("Error: Not a polynomial; solution set is %s. Try again.\n", hdnum ? "null" : "the set of real numbers");
						hdnum = hdnum_o;
						loopvar = 1;
					}
				}
			}
		}

		//prints out coeffs for debugging
		//printIntArray(coeffs, hdnum);

		/*
			***************************
			** RATIONAL ROOT FINDING **
			***************************
		*/
		float zeroes[hdnum]; //list of zeroes
		int zeroes_n[hdnum]; //numerators
		int zeroes_d[hdnum]; //denominators
		int roots_found = 0; //index of zeroes[] to edit
		fill(zeroes, 0.0, hdnum);
		fillInt(zeroes_n, 0, hdnum);
		fillInt(zeroes_d, 1, hdnum);

		//if constant is zero
		if(coeffs[0] == 0){
			roots_found++;
			int shft; //for shifting the coefficients around
			while(coeffs[0] == 0){
				hdnum--;
				for(shft = 0; shft < hdnum; shft++){
					coeffs[shft] = coeffs[shft+1];
				}
			}
		}

		int const_coeff_fc = ((int) sqrt(fabs(coeffs[0]))) * 4; //number of maximum factors of a0. supposedly
		int const_coeff_f[const_coeff_fc]; //factors of a0
		factor(coeffs[0], const_coeff_f, const_coeff_fc);
		//printIntArray(const_coeff_f, const_coeff_fc); //for checking

		int highdeg_coeff_ff = 1;
		int c_ctr = 0;
		float x,y;
		//printf("Max factors of a0: %d\n", const_coeff_fc);
		while(highdeg_coeff_ff <= fabs(coeffs[hdnum-1])){
			if(coeffs[hdnum-1]%highdeg_coeff_ff == 0){
				for(c_ctr=0; c_ctr<const_coeff_fc; c_ctr++){
					x = (float) const_coeff_f[c_ctr] / highdeg_coeff_ff;
					y = polyfxn(coeffs, hdnum, x);
					/*
					//Block of output code for debugging
					printf("***\nx:%lf:\n", x);
					printf("y:%lf:\n", y);
					printf("y times 1000000:%lf:\n", y*(1000000));
					printf("abs int y times 10-6:%lf:\n", (int) fabs(y*(1000000)));
					printf("%d / %d\n***\n\n", const_coeff_f[c_ctr], highdeg_coeff_ff);
					*/
					if((int) fabs(y*1000000) == 0){
						if(!isHere(zeroes, x, roots_found)){
							zeroes[roots_found] = x;
							/*
							if(const_coeff_f[c_ctr] % highdeg_coeff_ff != 0) printf("Factor: %d/%d\n\n", const_coeff_f[c_ctr], highdeg_coeff_ff);
							else printf("Factor: %d\n\n", (int) zeroes[roots_found]);
							*/
							zeroes_n[roots_found] = const_coeff_f[c_ctr];
							zeroes_d[roots_found] = highdeg_coeff_ff;
							roots_found++;
						}
					}
				}
			}
			highdeg_coeff_ff++;
			//printf("highdeg_coeff_ff:%d:\n", highdeg_coeff_ff);
		}

		//end of the root finding loop
		//printf("\n***PRINTING ZEROES FOUND***\n");
		//printFloatArray(zeroes, roots_found);

		/*
			************
			** OUTPUT **
			************
		*/
		//sort(zeroes, roots_found);
		//printFloatArray(zeroes, roots_found);
		sortND(zeroes_n, zeroes_d, roots_found);
		//printIntArray(zeroes_n, roots_found);
		//printIntArray(zeroes_d, roots_found);
		printf("Factors : ");
		int gcf_nd;
		int ndx_out = 0;
		for(ndx_out = 0; ndx_out < roots_found; ndx_out++){
			if(zeroes_n[ndx_out] % zeroes_d[ndx_out] == 0){
				printf("%s%d", ndx_out ? ", " : "", zeroes_n[ndx_out] / zeroes_d[ndx_out]);
			} else {
				gcf_nd = gcf(zeroes_n[ndx_out], zeroes_d[ndx_out]);
				if(gcf_nd < 0) gcf_nd *= -1;
				printf("%s%d/%d", ndx_out ? ", " : "", zeroes_n[ndx_out] / gcf_nd, zeroes_d[ndx_out] / gcf_nd);
			}
		}

		/*
			********************
			** NEW POLYNOMIAL **
			********************
		*/
		do{
			printf("\nInput new polynomial? ");
			fgets(yn, 10, stdin);
			trim(yn);
			if(strcasecmp(yn, "yes") == 0){
				break;
			} else if(strcasecmp(yn, "no") == 0){
				printf("\nTerminating program.\n");
				program_loop = 0;
				break;
			} else {
				printf("Please enter only 'yes' or 'no'.\n");
			}
		}while(1);
	}while(program_loop);
}

/*
*******************************
** LIST OF VARIABLES IN MAIN **
*******************************
** Name									Type			Loop Level?		Use **
** yn										char[]		0							Stores user input: continue program or not.
** program_loop					BOOLEAN		0							Continues program loop.
** high_deg							int				0							Stores user input: raw degree of polynomial.
** coeffs_list					char[]		0							Stores user input: raw list of coefficients.
** hdnum								int				0							Holds degree of polynomial.
** loopvar							int				0							Continues loops inside the program.
** coeff_s							char*			0							Holds substrings of tokenized coeffs_list
** coeffs_c							int				0							Index for coeffs[] array during coeffs. reading.
** coeffs								int[]			1							Array of integer coefficients.
** hdnum_o							int				1							Holds original value of hdnum; for when an error occurs after hdnum's value is changed.
** zeroes								float[]		1							Array of zeroes of the polynomial; for checking if such a zero was already obtained.
** zeroes_n							int[]			1							Array of zeroes' numerator; for fraction output.
** zeroes_d							int[]			1							Array of zeroes' denominator; for fraction output.
** roots_found					int				1							Holds number of zeroes found; for indicating which indices of the zeroes arrays are to be considered.
** shft									int				1							For shifting the coefficients if the constant is zero.
** const_coeff_fc				int				1							Holds the maximum number of factors of a0 or p.
** const_coeff_f				int[]			1							Array of factors of a0 or p.
** highdeg_coeff_ff			int				1							Holds a factor of an or q. Is iterated and used to continue a loop.
** c_ctr								int				1							For iterating through each factor of a0 or p.
** x, y									float			1							Holds the x and y values for a function.
** gcf_nd								int				1							Holds the GCF of the zero's numerator and denominator; for simplifying a fraction.
** ndx_out							int				1							For iterating through each zero's numerator and denominator.
*/
