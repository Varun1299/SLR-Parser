#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "stack.h"
#include<string.h>

void parse_char(char a, struct Stack** root, Production *p, Alphabet *table){
	int flag = 0;
	while (table -> next != NULL){
		if (table -> alphabet == a){
			flag = 1;
			break;
		}
		table = table -> next;
	}
	if (flag == 0){
		printf("%c is not a valid symbol\n", a);
		return ;
	}
	flag = 0;
	int st = (*root) -> state;
	Node *state_node = table -> statesPtr;

	while (state_node -> next != NULL){
		if (state_node -> state == st){
			flag = 1;
			break;
		}
		state_node = state_node -> next;
	}
	if (flag == 0){
		printf("No action for character %c and state %d \n", a, st);
		return ;
	}
	flag = 0;

	char *act = state_node -> action;

	if (strcmp(act, "acc") == 0){
		printf("Accept");
		return;
	}
	else if (act[0] == 's'){
			char *ac = *(act + 1);
			int n = atoi(ac);
			push(root, n, a);
	}
	else{
		char *ac = *(act + 1);
		int n = atoi(ac);
		while (p -> next != NULL){
			if (p -> number == n){
				flag = 1;
				break;
			}
			p = p -> next;
		}

		char h = p -> head;
		char *b = p -> body;

		for (int i = 0; i < strlen(b); i++){
			DoubleStack *ds = pop(root);
			if (b[i] != ds -> symbol){
				printf("Error\n");
				return;
			}



		}
		printf("Production %c -> %s\n",h,b );

		while (table -> next != NULL){
			if (table -> alphabet == h){
				flag = 1;
				break;
			}
			table = table -> next;
		}


		flag = 1;
		int st = (*root) -> state;
		Node *state_node = table -> statesPtr;

		while (state_node -> next != NULL){
			if (state_node -> state == st){
				flag = 1;
				break;
			}
			state_node = state_node -> next;
		}
		if (flag == 0){
			printf("No action for terminal %c and state %d \n", h, st);
			return ;
		}
		flag = 0;
		char *act = state_node -> action;
		char *ac = *(act + 1);
		int n = atoi(ac);

		push(root, n, h)


	}
	



}

