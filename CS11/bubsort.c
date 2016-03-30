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

void sortList(List **head){
	int loop = 0;// loop condition
	if(*head == NULL || (*head) -> next == NULL){// if no nodes or only 1 node no need to sort
		return;
	}
	while(loop == 0){
		List **prev = head; // pointer pointing to the address of the head node
		List *current = *head; // the head node
		List *next = (*head) -> next; // the next node of the head
		loop = 1;
		while(next != NULL){
			if(current->val > next->val){
				current -> next = next -> next;//changes current's next node into next's next node
				next -> next = current;// next's next node becomes current
				*prev = next;// next becomes the new head
				loop = 0;// to continue loop
			}
			prev = &current -> next; // current's next node will become new head
			current = next; // current will become its next node
			next = next -> next; // next will become its next node
		}
	}
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
    sortList(&list);
    popList(list);
}
