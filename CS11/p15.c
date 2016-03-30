#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List{
    int val;
    struct List * next;
} List;

List * addBack(List * list, int val){
    if(list){
        List * node = list;
        while(node->next) node = node->next;
        node->next = (List*) malloc(sizeof(List));
        node = node->next;
        node->val = val;
        node->next = NULL;
    } else {
        list = (List*) malloc(sizeof(List));
        list->val = val;
        list->next = NULL;
    }
    return list;
}

List * addFront(List * list, int val){
    List * node = (List*) malloc(sizeof(List));
    node->val = val;
    node->next = list;
    return node;
}

void viewList(List * list){
    List * ptr = list;
    while(ptr){
        printf("~ %d\n", ptr->val);
        ptr = ptr->next;
    }
    printf("~~~~~\n");
}

List * sortList(List * list){
    if(!list) return NULL;
    if(!(list->next)) return list;
    List * ptr = list->next;
    List * ptr_bef = list;
    List * ptr_lim = ptr;
    while(ptr){
        //remove ptr and insert it somewhere else
        ptr_lim = ptr->next;
        ptr_bef->next = ptr_lim;
        ptr->next = NULL;
        ptr_bef = list;
        //viewList(list);

        //insert the ptr somewhere
        if(ptr_bef->val >= ptr->val){ //head
            ptr->next = ptr_bef;
            list = ptr;
        } else {
            while(ptr_bef->next != ptr_lim){
                if(ptr_bef->next->val >= ptr->val){
                    break;
                }
                ptr_bef = ptr_bef->next;
            }
            ptr->next = ptr_bef->next;
            ptr_bef->next = ptr;
        }
        while(ptr_bef->next != ptr_lim) ptr_bef = ptr_bef->next;
        ptr = ptr_lim;
    }
    return list;
}

void popList(List * list){
    List * ptr = list;
    while(ptr){
        ptr = ptr->next;
        printf(":: %d\n", list->val);
        free(list);
        list = ptr;
    }
}

int main(){
    char string[100];
    List * list = NULL;
    printf("Enter numbers: ");
    fgets(string, 100, stdin);
    char * tok = strtok(string, " ,");
    while(tok){
        list = addBack(list, atoi(tok));
        tok = strtok(NULL, " ,");
    }
    viewList(list);
    list  = sortList(list);
    popList(list);
}
