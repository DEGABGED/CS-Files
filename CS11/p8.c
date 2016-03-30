#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct point{
    float x;
    float y;
    struct point * next;
} Point;

Point * addPointX(Point * set, float x){
    if(!set){
        set = (Point*) malloc(sizeof(Point));
        set->x = x;
        set->y = 0;
        set->next = NULL;
        return set;
    } else {
        Point * ptr = set;
        while(ptr->next) ptr = ptr->next;
        ptr->next = (Point*) malloc(sizeof(Point));
        ptr = ptr->next;
        ptr->x = x;
        ptr->y = 0;
        ptr->next = NULL;
        return set;
    }
}

Point * updatePointY(Point * set, float y){
    Point * ptr = set;
    while(ptr){
        ptr->y = y;
        ptr = ptr->next;
    }
    return set;
}

void viewPoints(Point * set){
    Point * ptr = set;
    while(ptr){
        printf("(%.2f, %.2f)\n", ptr->x, ptr->y);
        ptr = ptr->next;
    }
}

Point * sortPoints(Point * list){
    //sort list (bubble)
    Point * ptr = list;
    Point * tmp = NULL;
    Point * ptr2 = list; //handles the pointer to the new node
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
                    if(ptr->x > ptr->next->x){
                        //printf("Headswap %.2f & %.2f\n", ptr->x, ptr->next ? ptr->next->x : 0.01);
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
                    if(ptr->x > ptr->next->x){
                        //printf("Swap %.2f & %.2f\n", ptr->x, ptr->next ? ptr->next->x : 0.01);
                        ptr2->next = ptr->next;
                        tmp = ptr->next->next;
                        ptr->next->next = ptr;
                        ptr->next = tmp;
                        isSwap = 1;
                        //printf("before ptr2->next\n");
                        ptr2 = ptr2->next;
                    } else {
                        ptr2 = ptr;
                        ptr = ptr->next;
                    }
                }
                //printf("before viewlist\n");
                //viewWordList(list);
            } else {
                break;
            }
            //viewPoints(list);
            //printf("~~~");
        }
        //printf("\n");
    }
    return list;
}

void freeList(Point * list){
    Point * ptr = list;
    while(ptr){
        ptr = ptr->next;
        free(list);
        list = ptr;
    }
}

int main(){
    char string[200];
    char * token;
    Point * set = NULL;

    printf("Enter x values of the points:\n");
    fgets(string, 100, stdin);
    token = strtok(string, " ,");
    while(token){
        set = addPointX(set, atof(token));
        token = strtok(NULL, " ,");
    }
    Point * ptr = set;

    printf("Enter y values of the points:\n");
    fgets(string, 100, stdin);
    token = strtok(string, " ,");
    while(token && ptr){
        ptr->y = atof(token);
        ptr = ptr->next;
        token = strtok(NULL, " ,");
    }

    set = sortPoints(set);
    viewPoints(set);
    freeList(set);
}
