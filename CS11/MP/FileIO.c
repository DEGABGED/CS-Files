#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRLEN 200

FILE * addData(FILE * fp){
    printf("Enter a string: ");
    char string[STRLEN];
    fgets(string, STRLEN, stdin);
    fputs(string, fp);
    return fp;
}

void viewData(FILE * fp){
    char string[STRLEN];
    fgets(string, STRLEN, fp);
    while(string[0] != '\0'){
        printf("%s", string);
        string[0] = '\0';
        fgets(string, STRLEN, fp);
    }
}

int main(){
    FILE * fpw;
    FILE * fpr;
    char choice;
    do{
        printf("(A)dd, (V)iew, (Q)uit: ");
        scanf("%c", &choice);
        getchar();
        switch(choice){
            case 'a':
                fpw = fopen("library.txt", "a+");
                if(fpw) fpw = addData(fpw);
                fclose(fpw);
                break;
            case 'v':
                fpr = fopen("library.txt", "r");
                if(fpr) viewData(fpr);
                fclose(fpr);
                break;
            case 'q':
                printf("Goodbye!\n"); break;
        }
    }while(choice != 'q');
}
