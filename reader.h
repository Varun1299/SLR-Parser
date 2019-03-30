#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"


Production *productionFileReader(char *fileName)
{

	/*Reads all production rules from a file and creates a linked list where each node stores the head and body of a production.*/
	char head, ch;
	char body[256];
	FILE *filePtr;
	int numTerminals, numNonTerminals, count = 0, k , flag;
	Production *headPtr;
	Production *tailPtr;
 

	filePtr = fopen(fileName, "r");
    

	if(filePtr == NULL)
	{
		//If file does not exist
		printf("Could not open file :( ");
		exit(-1);
	}
    
    //Reads number of terminals and non-terminals
    numTerminals = fgetc(filePtr) - '0';
    fgetc(filePtr);
    numNonTerminals = fgetc(filePtr) - '0';
    fgetc(filePtr);
    fgetc(filePtr);

    //Reads the productions
	while(1)
	{
		if (flag)
		{
			break;
		}
		head = fgetc(filePtr);
		fgetc(filePtr);
		k = 0;
		while(1)
		{	
			ch = fgetc(filePtr);
			if(ch == EOF)
			{
				body[k] = '\0';
				flag = 1;
				break;
			}
			if (ch == '\n')
			{
				body[k] = '\0';
				break;
			}
			body[k] = ch;
			k++;
		}

		Production *production = (Production *)malloc(sizeof(Production));
		production->number = count+1;
		production->head = head;
		strcpy(production->body, body);
		production->next = NULL;

		if(count == 0)
		{
		    headPtr = production;
		    tailPtr = production;
		}
		else
		{
			tailPtr->next = production;
			tailPtr = production;
		}
		count++;
		
	}

	return headPtr;
}

void addNode(Alphabet *alphabetPtr, Node *node)
{
	//Adds a new node to end of linked list whose head is pointed to by alphabetPtr.
	Node *tmpPtr = alphabetPtr->statesPtr;
	if (tmpPtr == NULL)
	{
		alphabetPtr->statesPtr = node;
	}
	else
	{
		while(tmpPtr->next != NULL)
		{
			tmpPtr = tmpPtr->next;
		}
		tmpPtr->next = node;
	}
}


Alphabet *parseTableReader(char *fileName)
{

		/*
	Reads the file with parse table to create a linked list of nodes, where each node is head of another linked list.
	The primary linked list store alphabets. The secondary linked list store the state the action needed to be taken when we see the correspanding alhabet and state.
	*/
	FILE *filePtr;
	char ch;
	int state, flag, nodeCount, count = 0;
	Alphabet *headPtr;
	Alphabet *tailPtr;
	char buffer[10];
 

	filePtr = fopen(fileName, "r");
	if(filePtr == NULL)
	{
		printf("Could not open file :(");
		exit(-1);
	}
	
	//Follwing while loop reads the terminals/non-terminals and creates a linked list containing them.
	while(1)
	{
		ch = fgetc(filePtr);
		if(ch == '\n')
		{
			break;
		}
		else if(ch != ',')
		{
			Alphabet *symbol = (Alphabet *)malloc(sizeof(Alphabet));
			symbol->alphabet = ch;
			symbol->next = NULL;
			symbol->statesPtr = NULL;

			if(count == 0)
			{
			    headPtr = symbol;
			    tailPtr = symbol;
			    count++;
			}
			else
			{
				tailPtr->next = symbol;
				tailPtr = symbol;
			}
		}
	}

	//Following while loop reads the parse table entries and stores them in the linked list of their corresponding alphabet.
	//The state is stored as an attribute.
	flag = 0;
	while(1)
	{
		Alphabet *tmpPtr = headPtr;
		fscanf(filePtr, "%d", &state);
		// state  = getc(filePtr) - '0';
		fgetc(filePtr);
		count = 0;
		while(1)
		{
			ch = fgetc(filePtr);

			if (ch == ',')
			{
				if (count != 0)
				{

					Node *node = (Node *)malloc(sizeof(Node));
					node->state = state;
					strcpy(node->action, buffer);

					node->next = NULL;


					addNode(tmpPtr, node);

				}
				tmpPtr = tmpPtr->next;
				count = 0;
			}
			else if (ch == '\n')
			{
				Node *node = (Node *)malloc(sizeof(Node));
				node->state = state;
				strcpy(node->action, buffer);

				node->next = NULL;
				addNode(tmpPtr, node);
				break;
			}
			else if (ch == EOF)
			{
				flag = 1;
				break;
			}
			else
			{	
				buffer[count] = ch;
				buffer[count + 1] = '\0';
				count++;
			}

		}
		if (flag == 1)
		{
			break;
		}


	}





    return headPtr;
}
