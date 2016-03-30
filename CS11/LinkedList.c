#include <stdio.h>
#include <stdlib.h>

typedef struct PtrLinkedList{
    int data;
	struct PtrLinkedList * next;
} List;

List * createList(List * list, int data){
	//printf("in createlist\n");
    list = (List*) malloc(sizeof(List));
	list->data = data;
	list->next = NULL;
	return list;
}

List * addNode(List * list, int data){
	//printf("in addnode\n");
	if(!list){
		return createList(list, data);
	}

	List * node = (List*) malloc(sizeof(List));
	node->data = data;
	node->next = list;
	return node;
}

void viewList(List * list){
	List * ptr = list;
    printf("[");
	while(ptr != NULL){
        printf("%d%s", ptr->data, ptr->next ? ", " : "");
		ptr = ptr->next;
	}
    printf("]\n");
}
/*
List * deleteNode(List * list, int data){
	//check if said data is present
	List * ptr = list;
	List * before_ptr = NULL;
	while(ptr != NULL){
		if(ptr->data == data)
			break;
		else{
			ptr = ptr->next;
			before_ptr = before_ptr ? before_ptr->next : list;
		}
	}

	if(ptr==NULL){
		printf("Not found.\n");
		return list;
	}

	if(before_ptr==NULL){
		if(ptr->next==NULL){
			free(list);
			return NULL;
		} else {
			list = list->next;
			free(ptr);
			return list;
		}
	}

	before_ptr->next = ptr->next;
	free(ptr);
	return list;
}
*/

List * sortList(List * list){
    List * tmp = NULL;
    List * ptr = list; //ptr and ptr->next will swap
    List * ptr2 = list; //handles the pointer to the new node
    int isSwap = 1;
    while(isSwap){
        isSwap = 0;
        printf("loop start\n");
        List * ptr = list; //ptr and ptr->next will swap
        List * ptr2 = list; //handles the pointer to the new node
        while(ptr){
            if(ptr->next){
                if(ptr == ptr2){ //start of the list
                    if(ptr->data < ptr->next->data){
                        list = ptr2->next;
                        tmp = ptr->next->next;
                        ptr->next->next = ptr;
                        ptr->next = tmp;
                        printf("Tmp : %d\n", tmp->data);
                        isSwap = 1;
                        ptr = list;
                    } else {
                        ptr = ptr->next;
                    }
                } else {
                    if(ptr->data < ptr->next->data){
                        ptr2->next = ptr->next;
                        tmp = ptr->next->next;
                        ptr->next->next = ptr;
                        ptr->next = tmp;
                        printf("Tmp : %d\n", tmp ? tmp->data : 0);
                        isSwap = 1;
                        printf("before ptr2->next\n");
                        ptr2 = ptr2->next;
                    } else {
                        ptr2 = ptr;
                        ptr = ptr->next;
                    }
                }
                printf("before viewlist\n");
                viewList(list);
            } else {
                break;
            }
        }
        printf("\n");
    }
    return list;
}

void freeList(List * list){
	List * ptr = list;
	while(list != NULL){
		ptr = ptr->next;
		printf("Freeing : %d\n", list->data);
		free(list);
		list = ptr;
	}
	return;
}

int main(){
	char ch;
	int data;
	List * list = NULL;
	do{
		printf("\n(A)dd / (V)iew / (S)ort / (D)elete / (Q)uit: ");
		ch = fgetc(stdin);
		switch(ch){
			case 'a':
				printf("Enter data: ");
				scanf("%d", &data);
                list = addNode(list, data);
				break;
			case 'v':
				viewList(list);
				break;
			case 's':
				list = sortList(list);
				break;
			case 'd':
                break;
			case 'q': printf("Bye!\n"); break;
			default: printf("Try again.\n"); break;
		}
		//printf("Head: %d; End: %d\n", list ? list->data : 0, end ? end->data : 0);
        getchar();
	}while(ch != 'q');
	if(list) freeList(list);
}
