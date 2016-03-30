/*
	**
	** Name: Francis Zac Quintin dela Cruz
	** Student Number: 2015-08086
	** Section: THXY1
	** Description: A program which takes in a polynomial's degree
	**	and coefficients, and outputs the rational roots of the polynomial
	**	found through the rational root theorem. The program has 8 functions;
	**	int main() included. The source code is around 400 lines; counting
	**	comments.
	**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define HD_MAX_DIGITS 5
/*Arbitrarily defined limit of digits for the degree of the polynomial*/

/*
	**************************
	** SIMPLE ARRAY EDITORS **
	**************************
*/
/*Removes whitespaces
Used before input validation*/
void trim(char string[]){
	int ndx_s = 0; /*start of string*/
	int ndx_e = strlen(string) - 1; /*end of string*/

	/*Removes whitespaces after text*/
	while(string[ndx_e] == ' ' || string[ndx_e] == '\t' || string[ndx_e] == '\n'){
		string[ndx_e] = '\0';
		ndx_e--;
	}
	ndx_e++;

	int ndx_s_out = 0; /*start of string w/o whitespaces*/
	for(ndx_s = 0; ndx_s <= ndx_e; ndx_s++){
		if(string[ndx_s] == ' ' || string[ndx_s] == '\t' || string[ndx_s] == '\n'){
			ndx_s_out++;
		} else {
			break;
		}
	}

	/*shifting of characters, removing whitespace*/
	if(ndx_s_out){
		for(ndx_s = 0; ndx_s + ndx_s_out <= ndx_e; ndx_s++){
			string[ndx_s] = string[ndx_s + ndx_s_out];
		}
	}
}

/*Swaps the values in 2 addresses
Used for the sortInt function*/
void swap(int * a, int * b){
	static int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
	*********************************
	** CHECKERS: RETURNS "BOOLEAN" **
	*********************************
*/
/*Checks if char string is an integer. If so, int address gets the int value
and function returns 0. If not, returns 1. Used for two purposes: one for degree
input, the other for coefficient input*/
int isNotNumber(char string[], int * number, int isDegree){
	/*check if entire string is composed of numbers and the negative sign*/
	trim(string);
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

	/*Converts string to integer,
	then checks integer if it's negative, 0, or positive*/
	*number = atoi(string);
	if(*number==0){
		if(isDegree){
			printf("Error: Input can't be 0. Try again.\n");
			/*Possible that 0 is allowed; but it's a special test case anyway*/
		} else {
			return 0; /*for coefficients, 0 is a possible input*/
		}
	} else if(*number < 0){
		if(isDegree){
			printf("Error: Input is negative. Try again.\n");
		} else {
			return 0; /*for coefficients, negative numbers are allowed*/
		}
	} else {
		return 0;
	}
	return 1;
}

/*Searches float array for a num; outputs 1 if found; 0 if not
Used in finding out if a root has been found before to avoid repetition
in the output.*/
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

/*Sorts the output (2 arrays) (Bubble Sort)
Used once to sort the fractional outputs*/
void sortND(int n[], int d[], int len){
	int swapped = 1, ndx;
	len--;
	do{
		swapped = 0;
		for(ndx = 0; ndx < len; ndx++){
			if(((float)n[ndx] / d[ndx]) > ((float)n[ndx+1] / d[ndx+1])){
				swap(&n[ndx], &n[ndx+1]);
				swap(&d[ndx], &d[ndx+1]);
				swapped = 1;
			}
		}
	}while(swapped);
}

/*
	***********************
	** NUMBER PROCESSING **
	***********************
*/
/*Takes integer num and writes integer factors of num onto factors[]
Used for finding factors of p and q.*/
void factor(int num, int factors[], int factors_l){
	num = fabs(num);
	int mdpt = (int) sqrt(num);
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
	char yn[10]; /*String; holds a yes/no response*/
	int program_loop = 1; /*if 0, program stops*/
	char high_deg[100]; /*String; holds the highest degree from user*/
	char coeffs_list[6*100]; /*String; holds the list of coefficients from user*/
	int hdnum, hdnum_o; /*Holds the higest degree (int)*/
	int loopvar = 1; /*if 0, checking loops stop;*/
	char * coeff_s; /*INPUT: string to hold each coefficient in the input string*/
	int coeffs_c; /*INITIALIZED INSIDE: counter of the while loop*/
	int ndx; /*For use in for loops that access array elements*/
	float x,y; /*stores x and f(x)*/
	int roots_found; /*stores number of roots found; reinitialized every program loop*/
	int highdeg_coeff_ff; /*stores a factor of an; reinitialized every program loop*/
	do{
		loopvar = 1;
		/*
			**************************
			** HIGHEST DEGREE INPUT **
			**************************
		*/
		/*loop to validate first input*/
		while(loopvar){
			printf("\nEnter the highest degree of the input polynomial: ");
			fgets(high_deg, 100, stdin);
			if(strchr(high_deg, '.') != NULL){
				printf("Error: Degree must be an integer. Try again\n");
				continue;
			}
			loopvar = isNotNumber(high_deg, &hdnum, 1);
		}

		hdnum++;
		int coeffs[hdnum]; /*int array of coefficients*/

		/*
			************************
			** COEFFICIENTS INPUT **
			************************
		*/
		loopvar = 1; /*reinitializes loopvar*/
		/*loop to validate second input*/
		hdnum_o = hdnum; /*Stores the original value of hdnum for when an error
		with the degree occurs after changing it*/
		while(loopvar){
			/*gets the string of numbers;
			strtok usage from http://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm*/
			coeff_s = NULL;
			printf("\nEnter %d coefficients starting from the 0th degree.", hdnum);
			printf("\nSeparate each input from a comma: ");
			fgets(coeffs_list, 6*100, stdin);
			if(strchr(coeffs_list, '.') != NULL){
				printf("Error: Coefficients must be integers. Try again\n");
				continue;
			}

			/*separates string into substrings with ',' as a delimiter*/
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
					/*At this part, input is finished and validated, and the coefficients
					in question are being validated.*/
					loopvar = 0;

					/*If more than the asked number of coefficients were entered*/
					if(coeff_s != NULL){
						printf("Warning: More than what was asked for was entered. "
							"Program will accept only the first %d coefficients.\n", hdnum);
					}

					/*If the last coefficient/s is/are zero, which changes the degree of the polynomial.*/
					if(coeffs[hdnum-1] == 0){
						printf("Warning: The last coefficient/s is/are 0. "
							"Program will change the degree of the entire polynomial accordingly.\n");
						while(coeffs[hdnum-1] == 0){
							hdnum--;
						}
					}

					/*If the degree of the polynomial is 1 or 0*/
					if(hdnum <= 1){
						printf("Error: Not a polynomial; solution set is %s. Try again.\n",
							hdnum ? "null" : "the set of real numbers");
						hdnum = hdnum_o;
						loopvar = 1;
					}
				}
			}
		}

		/*
			***************************
			** RATIONAL ROOT FINDING **
			***************************
		*/
		float zeroes[hdnum]; /*list of zeroes*/
		int zeroes_n[hdnum]; /*numerators*/
		int zeroes_d[hdnum]; /*denominators*/
		roots_found = 0; /*index of zeroes[] to edit; no. of roots found*/

		/*if constant is zero*/
		if(coeffs[0] == 0){
			zeroes[roots_found] = 0;
			zeroes_n[roots_found] = 0;
			zeroes_d[roots_found] = 1;
			roots_found++;
			int shft; /*used for shifting the coefficients around*/
			/*"Divides" the polynomial by x*/
			while(coeffs[0] == 0){
				hdnum--;
				for(shft = 0; shft < hdnum; shft++){
					coeffs[shft] = coeffs[shft+1];
				}
			}
		}

		int const_coeff_fc = ((int) sqrt(fabs(coeffs[0]))) * 4; /*number of maximum factors of a0*/
		int const_coeff_f[const_coeff_fc]; /*array to store factors of a0*/
		factor(coeffs[0], const_coeff_f, const_coeff_fc);

		highdeg_coeff_ff = 1; /*stores a factor of an*/

		/*Loop to find the roots
		highdeg_coeff_ff will be incremented and used if it is a factor of an*/
		while(highdeg_coeff_ff <= fabs(coeffs[hdnum-1])){
			if(coeffs[hdnum-1]%highdeg_coeff_ff == 0){
				for(ndx=0; ndx<const_coeff_fc; ndx++){
					x = (float) const_coeff_f[ndx] / highdeg_coeff_ff;
					y = polyfxn(coeffs, hdnum, x);
					/*if y is a zero, and if the zero hasn't been already found*/
					if((int) fabs(y*1000000) == 0){
						if(!isHere(zeroes, x, roots_found)){
							zeroes[roots_found] = x;
							zeroes_n[roots_found] = const_coeff_f[ndx];
							zeroes_d[roots_found] = highdeg_coeff_ff;
							roots_found++;
						}
					}
				}
			}
			highdeg_coeff_ff++;
		}

		/*
			************
			** OUTPUT **
			************
		*/
		sortND(zeroes_n, zeroes_d, roots_found);
		printf("Factors : ");
		for(ndx = 0; ndx < roots_found; ndx++){
			if(zeroes_n[ndx] % zeroes_d[ndx] == 0){ /*Zero is an integer*/
				printf("%s%d", ndx ? ", " : "", zeroes_n[ndx] / zeroes_d[ndx]);
			} else { /*Zero is a fraction*/
				printf("%s%d/%d", ndx ? ", " : "", zeroes_n[ndx], zeroes_d[ndx]);
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

	return 1;
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
** roots_found					int				0							Holds number of zeroes found; for indicating which indices of the zeroes arrays are to be considered.
** shft									int				1							For shifting the coefficients if the constant is zero.
** const_coeff_fc				int				1							Holds the maximum number of factors of a0 or p.
** const_coeff_f				int[]			1							Array of factors of a0 or p.
** highdeg_coeff_ff			int				1							Holds a factor of an or q. Is iterated and used to continue a loop.
** x, y									float			0							Holds the x and y values for a function.
** ndx									int				0							For use in certain for loops that access an array's elements.
**
** Note: Loop Level is the number of loops the variables are in.
*/
