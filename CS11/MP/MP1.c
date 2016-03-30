#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Removes whitespaces.
void trim(char string[]){
	printf("\n***BEFORE TRIM:%s:***", string);
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
	printf("\n***AFTER TRIM:%s:***\n", string);
}

//Checks if char string is an integer. If so, int address gets the int value and function returns 1. If not, returns 0.
int isNotNumber(char string[], int * number, int isDegree){
	//check if entire string is numbers
	trim(string);
	printf("***\nstring[]: %s\n***\n\n", string);
	static const char allowed[] = "-1234567890";
	int ndx = 0;
	int len = strlen(string);
	for(;ndx < len; ndx++){
		if(strchr(allowed, string[ndx]) == NULL){
			printf("Error: Input not a number. Try again.\n");
			return 1;
		}
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
		if((strcmp(string,"0\n") != 0) && (strcmp(string,"0") != 0)){
			printf("Error: Input not a number. Try again.\n"); //Theoretically this if part of the if else statement is not needed anymore. I'm still leaving it here for now.
		} else {
			if(isDegree){
				printf("Error: Input can't be 0. Try again.\n"); //Possible that 0 is allowed; but it's a special test case anyway
			} else {
				return 0; //for coefficients, 0 is a possible input
			}
		}
	}
	return 1;
}

//Searches float array for a num; outputs 1 if found; 0 if not
int isHere(float a[], float num, int roots){
	int ndx = 0;
	for(;ndx<roots;ndx++){
		if(num == a[ndx]) return 1;
	}
	return 0;
}

//Initiallizes float array values all to num
void fill(float a[], float num, int len){
	for(;len>=0;len--){
		a[len] = num;
	}
}

//Swaps the values in 2 addresses
void swap(int * a, int * b){
	static int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//Sorts a numerical array. (Bubble)
void sort(int a[], int len){
	int swapped = 1, ndx;
	len--;
	do{
		swapped = 0;
		for(ndx = 0; ndx < len; ndx++){
			if(a[ndx] > a[ndx+1]){
				swap(&a[ndx], &a[ndx+1]);
				swapped = 1;
			}
		}
	}while(swapped)
}

//Prints Integer Array
void printIntArray(int c[], int c_len){
	printf("***PRINTING***\n");
	int ctr = 0;
	for(; ctr<c_len; ctr++){
		printf("%d\n", c[ctr]);
	}
	printf("***FINISHED***\n\n");
}

//Prints Float Array; specifically list of factors in floating point
void printFloatArray(float c[], int c_len){
	printf("***PRINTING***\n");
	int ctr = 0;
	for(; ctr<c_len; ctr++){
		printf("%.3f\n", c[ctr]);
	}
	printf("***FINISHED***\n\n");
}

//Takes integer x; outputs integer factors of x onto array
void factor(int num, int factors[], int factors_l){
	printf("In factor function\n");
	num = fabs(num);
	int mdpt = (int) sqrt(num);
	printf("num:%d mdpt:%d\n", num, mdpt);
	int f = 1;
	int ctr = 0;
	for(; f<=mdpt; f++){
		if(num%f==0){
			factors[ctr] = f;
			ctr++;
			factors[ctr] = -f;
			ctr++;
			if((f != mdpt) || (f == 1)){
				printf("here");
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

//Takes input x and a polynomial's coefficients; outputs y
float polyfxn(int coeff[], int coeff_l, float x){
	int ctr = 0;
	float y = 0;
	for(; ctr<coeff_l; ctr++){
		y += (coeff[ctr] * pow(x, ctr));
	}
	return y;
}

int main(){
	char yn[10];
	int program_loop = 1;
	do{
		/*
			***************
			** VARIABLES **
			***************
		*/
		char high_deg[6]; //input string; holds the highest degree directly from user
		char coeffs_list[6*100]; //input string; holds the list of coefficients directly from user
		int hdnum; //holds the higest degree (int)
		int loopvar = 1; //if 0; checking loop stops;
		char * coeff_s; //string to hold each coefficient in the input string
		int coeffs_c; //counter of the while loop

		/*
			**************************
			** HIGHEST DEGREE INPUT **
			**************************
		*/
		//loop to inputcheck first input
		while(loopvar){
			high_deg[4] = '\0';
			printf("\nEnter the highest degree of the input polynomial: ");
			fgets(high_deg, 6, stdin);
			if((high_deg[4]!='\0') && (high_deg[4]!='\n')) while(getchar() != '\n');
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
					printf("Error: incomplete coefficients. Try again\n");
					break;
				} else {
					if(isNotNumber(coeff_s, &coeffs[coeffs_c], 0)){
						break;
					}
				}
				coeff_s = strtok(NULL, ",");
				coeffs_c++;
				if(coeffs_c >= hdnum){
					//at this part, the input getting is finished and validated
					loopvar = 0;
					//checks if last coefficient is a zero
					//apparently you can help the user and consider the 0, and just change the degree
					/*
					if(coeffs[coeffs_c-1] == 0){
						printf("Error: coefficient of highest degree term can't be 0. Try again\n");
						loopvar = 1;
					}
					*/
					if(coeffs[hdnum-1] == 0){
						printf("Warning: coefficient of term of highest degree is 0. Program will change the degree of the entire polynomial.\n");
						while(coeffs[hdnum-1] == 0){
							hdnum--;
						}
					}
				}
			}
		}

		//prints out coeffs for debugging
		printIntArray(coeffs, hdnum);

		/*
			***************************
			** RATIONAL ROOT FINDING **
			***************************
		*/
		float zeroes[hdnum]; //list of zeroes
		int roots_found = 0; //index of zeroes[] to edit
		fill(zeroes, 0.0, hdnum);

		//if constant is zero
		if(coeffs[0] == 0){
			int shft; //for shifting the coefficients around
			while(coeffs[0] == 0){
				roots_found++;
				hdnum--;
				for(shft = 0; shft < hdnum; shft++){
					coeffs[shft] = coeffs[shft+1];
				}
			}
			printf("Factor: 0\n\n");
		}

		int const_coeff_fc = ((int) sqrt(fabs(coeffs[0]))) * 4; //number of maximum factors of a0. supposedly
		int const_coeff_f[const_coeff_fc]; //factors of a0
		factor(coeffs[0], const_coeff_f, const_coeff_fc);
		//printIntArray(const_coeff_f, const_coeff_fc); //for checking

		int highdeg_coeff_ff = 1;
		int c_ctr = 0;
		float x,y;
		printf("Max factors of a0: %d\n", const_coeff_fc);
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
							if(const_coeff_f[c_ctr] % highdeg_coeff_ff != 0) printf("Factor: %d/%d\n\n", const_coeff_f[c_ctr], highdeg_coeff_ff);
							else printf("Factor: %d\n\n", (int) zeroes[roots_found]);
							roots_found++;
						}
					}
				}
			}
			highdeg_coeff_ff++;
			//printf("highdeg_coeff_ff:%d:\n", highdeg_coeff_ff);
		}

		//end of the root finding loop
		printf("\n***PRINTING ZEROES FOUND***\n");
		printFloatArray(zeroes, roots_found);

		/*
			********************
			** NEW POLYNOMIAL **
			********************
		*/
		do{
			printf("Input new polynomial? ");
			fgets(yn, 10, stdin);
			if(strcasecmp(yn, "yes\n") == 0){
				break;
			} else if(strcasecmp(yn, "no\n") == 0){
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
