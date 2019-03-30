#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "stack.h"
#include<string.h>

int parse_char(char a, struct stackNode** root, Production *p, Alphabet *table){
	int flag = 0;
	while (table->next != NULL){  // finding the ternimal in the linked list corresponding to input

		if (table->alphabet == a){
			flag = 1;

			break;
		}
		table = table->next;
	}
	if (flag == 0){
		printf("%c is not a valid symbol\n", a);
		return -1;
	}


	flag = 0;
	int st = (*root)->pair.state;  // ????????

	Node *state_node = table->statesPtr;


	while (1){  // finding the state corresponding to the top of the stack
		if (state_node->state == st){
			flag = 1;
			break;
		}

		if (state_node->next == NULL) break;
		state_node = state_node->next;

	}
	if (flag == 0){
		printf("No action for character %c and state %d \n", a, st);
		return -1;
	}
	flag = 0;


	char *act = state_node->action; //pick up the relevant action

	if (strcmp(act, "acc") == 0){  //aceept
		printf("ACCEPT \n");
		return -2;
	}
	else if (act[0] == 's'){   	//shift
			
			char *ac = (act + 1);  
			int n = atoi(ac);
			push(root, n, a);  	// pushing alphabet, shifted state on to stack
			return 0;
	}
	else{ 						//reduce
		char *ac = (act + 1);
		int n = atoi(ac);
		while (p->next != NULL){ // finding the relevant production
			if (p->number == n){
				flag = 1;
				break;
			}
			p = p->next;
		}



		char h = p->head;
		char *b = p->body;
		int len = strlen(b);

		if (b[strlen(b)-1] == '\r'){
			len = len - 1;
		}

		for (int i = len - 1; i >= 0; i--){    //popping out of stack if symbols match
			dataPair *ds = pop(root);

			if (b[i] != ds->symbol){
				printf("Error\n");
				return -1;
			}



		}


		printf("Production %c -> %s\n",h,b );  // printing out production

		while (table->next != NULL){
			if (table->alphabet == h){
				flag = 1;
				break;
			}
			table = table -> next;
		}

		//printf("KEK %c\n", table->alphabet);

		flag = 1;
		int st = (*root)->pair.state;
		Node *state_node = table->statesPtr;


		while (state_node->next != NULL){ // finding the GOTO value for the non-terminal
			
			if (state_node->state == st){


				flag = 1;
				break;
			}
			state_node = state_node->next;
		}




		if (flag == 0){
			printf("No action for terminal %c and state %d \n", h, st);
			return -1;
		}
		flag = 0;

		char *bct = state_node->action;

		n = atoi(bct);  

        push(root, n, h);  //pushing non-terminal, goto on to stack
        return 1;

       


	}
	



}

