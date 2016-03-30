#include <stdio.h>
#include <stdlib.h>

void main(){
	char string[50];
	printf("Enter file: ");
	fgets(string, 50, stdin);
	//remove the pesky \n
	int x;
	for(x=0; x<50; x++){
		if(string[x] == '\n'){
			string[x] = '\0';
		}
		if(string[x] == '\0'){
			break;
		}
	}
	FILE * fp = fopen(string, "rb");
	char ch;
	if(fp){
		ch = fgetc(fp);
		while(1){
			while(ch != '\n'){
				printf("\\%04x", ch);
				ch = fgetc(fp);
			}
			printf("\\%04x\n\n", ch);
			ch = fgetc(fp);
			if(feof(fp)) break;
		}
	} else {
		printf("no such file\n");
	}
}
