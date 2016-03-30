#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IOSHORT 20 //for integers
#define IOMED 100 //for long integers and others
#define IOLONG 200

typedef struct PtrLinkedList{
    void * data;
    float type;
    struct PtrLinkedList * next;
} APList;

typedef struct TimeBlock{
    float lower;
    float upper;
} TimeBlock;

APList * createAPList(APList * list, void * data, int type){
	//printf("in createlist\n");
    list = (APList*) malloc(sizeof(APList));
	list->data = data;
    list->type = type;
	list->next = NULL;
	return list;
}

APList * addAPNode(APList * list, void * data, int type){
	//printf("in addnode\n");
	if(!list){
		return createAPList(list, data, type);
	}

	APList * node = (APList*) malloc(sizeof(APList));
	node->data = data;
    node->type = type;
	node->next = list;
	return node;
}

//used specifically for CP20, where the type sub-variable holds the word
//  frequency, and the data sub-pointer holds the string
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

int main(){
    printf("\nProgram 19: Scheduling\n");
    printf("Please enter a series of time blocks: \n");
    char string[IOLONG];
    //fgets(string, IOLONG, stdin);
    strcpy(string, "8:30a-10a, 1130a-1p, 2:30p  -  4:00p");
    char * token;
    APList * list = NULL;
    token = strtok(string, " ,:-");
    int tok_int = 0, hrmin = 0, cycle = 0; //cycle: h-up -> min-up -> ap-up -> sosf.
    while(token){
        printf("%s\n", token);
        //parse token into a TimeBlock
        //data holds TimeBlock *; type holds lower bound
        if(cycle%6 == 0){
            list = addAPNode(list, NULL, 0);
            list->data = malloc(sizeof(TimeBlock));
            ((TimeBlock*) (list->data))->lower = 0;
            ((TimeBlock*) (list->data))->upper = 0;
        }
        hrmin = atoi(token);
        token+=strlen(token)-1;
        switch(cycle%3){
            case 0: //hour-upper
                if(hrmin < 24){ //only the hour is given
                    hrmin *= 100;
                    if(*token != 'p' && *token != 'a') cycle -= 2;
                }
                if(cycle%6 > 2){
                    ((TimeBlock*) (list->data))->upper += hrmin / 100;
                } else {
                    ((TimeBlock*) (list->data))->lower += hrmin / 100;
                    list->type += hrmin / 100;
                }
                //hrmin %= 100;
                cycle++;
            case 1: //minute-upper
                if(cycle%6 > 2){
                    ((TimeBlock*) (list->data))->upper += (float) (hrmin%100) / 100;
                } else {
                    ((TimeBlock*) (list->data))->lower += (float) (hrmin%100) / 100;
                    list->type += (float) (hrmin%100) / 100;
                }
                //get ampm
                cycle++;
            case 2: //ampm-upper
                if(*token == 'p' && hrmin/100 != 12){
                    if(cycle%6 > 2){
                        ((TimeBlock*) (list->data))->upper += 12.00;
                    } else {
                        ((TimeBlock*) (list->data))->lower += 12.00;
                        list->type += 12.00;
                    }
                }
                break;
        }
        //8:30a - 10:00a, 11:30a - 1:00p, 2:30p - 4:00p
        printf(":%d:%c:\n~%d~\n\n", hrmin, *token, cycle+1);
        cycle++;
        token = strtok(NULL, " ,:-");
    }

    //list = sortAPList(list, 1);

    //display
    APList * ptr = list;
    while(ptr){
        printf("%.2f-%.2f (key:%.2f)\n", ((TimeBlock*) (ptr->data))->lower, ((TimeBlock*) (ptr->data))->upper, ptr->type);
        ptr = ptr->next;
    }
/*
    //get the free times
    ptr = list;
    TimeBlock freetime;
    freetime.lower = 8.00;
    freetime.upper = 20.00;

    while(ptr){
        freetime.upper = ((TimeBlock*) (ptr->data))->lower;
        if(freetime.lower < freetime.upper){
            printf("%.2f-%.2f\n", freetime.lower, freetime.upper);
        }
        freetime.lower = ((TimeBlock*) (ptr->data))->upper;
        ptr = ptr->next;
    }
    freetime.upper = 20.00;
    if(freetime.lower < freetime.upper){
        printf("%.2f-%.2f\n", freetime.lower, freetime.upper);
    }
*/
    //free list
    ptr = list;
    while(ptr){
        ptr = ptr->next;
        free(list->data);
        free(list);
        list = ptr;
    }
}
