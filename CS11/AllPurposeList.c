#include <stdio.h>
#include <stdlib.h>

typedef struct PtrLinkedList{
	void * data;
    int type;
	struct PtrLinkedList * next;
} APList;

APList * createAPList(APList * list, void * data, int type){
	//printf("in createlist\n");
    list = (APList*) malloc(sizeof(APList));
	list->data = data;
    list->type = type;
	list->next = NULL;
	return list;
}

APList * addNode(APList * list, void * data, int type){
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

void viewAPList(APList * list){
	printf("in viewlist\n");
	APList * ptr = list;
	while(ptr != NULL){
		switch(ptr->type){
            case 0: printf("Val: NULL"); break;
            case 1: printf("Val: \'%d\'\n", *((int*) ptr->data)); break;
            case 2: printf("Val: \'%c\'\n", *((char*) ptr->data)); break;
            case 3: printf("Val: \'%s\'\n", (char*) ptr->data); break;
            case 4: printf("Val: \'%.3f\'\n", *((float*) ptr->data)); break;
        }
		ptr = ptr->next;
	}
}
/*
APList * deleteNode(APList * list, int data){
	//check if said data is present
	APList * ptr = list;
	APList * before_ptr = NULL;
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

APList sortAPList(APList * list){
    
}

void freeAPList(APList * list){
	APList * ptr = list;
	while(list != NULL){
		ptr = ptr->next;
		printf("Freeing:%p\n", list->data);
        free(list->data);
		free(list);
		list = ptr;
	}
	return;
}

int main(){
	char ch;
	int type;
    void * data = NULL;
	APList * list = NULL;
	APList * end = NULL;
	do{
		printf("\n(A)dd / (V)iew / (S)ort / (D)elete / (Q)uit: ");
		ch = fgetc(stdin);
		switch(ch){
			case 'a':
				printf("Enter data type 0-void, 1-int, 2-char, 3-string, 4-float: ");
				scanf("%d", &type);
                switch(type){
                    case 0:
                        break;
                    case 1:
                        printf("Enter integer: ");
        				getchar();
                        data = (int*) malloc(sizeof(int));
                        scanf("%d", (int*) data);
                        break;
                    case 2:
                        printf("Enter character: ");
        				getchar();
                        data = (char*) malloc(sizeof(char));
                        scanf("%c", (char*) data);
                        break;
                    case 3:
                        printf("Enter string: ");
        				getchar();
                        data = (char*) malloc(sizeof(char)*50);
                        scanf("%s", (char*) data);
                        break;
                    case 4:
                        printf("Enter float number: ");
        				getchar();
                        data = (float*) malloc(sizeof(float));
                        scanf("%f", (float*) data);
                        break;
                }
                list = addNode(list, data, type);
				break;
			case 'v':
				viewAPList(list);
				getchar();
				break;
			case 's':
				printf("none yet for sort\n");
				break;
			case 'd':
				printf("none yet\n");
                break;
			case 'q': printf("Bye!\n"); break;
			default: printf("Try again.\n"); break;
		}
		//printf("Head: %d; End: %d\n", list ? list->data : 0, end ? end->data : 0);
        getchar();
	}while(ch != 'q');
	if(list) freeAPList(list);
}
