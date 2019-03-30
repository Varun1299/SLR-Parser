#include <stdio.h>
#include <stdlib.h>
#include "defs.h"


Production *productionFileReader(char *fileName)
{
    printf("in prod\n");
	char head;
	char *body;
	FILE *filePtr;
	int numTerminals, numNonTerminals, count = 0;
	Production *headPtr;
	Production *tailPtr;
 

	filePtr = fopen(fileName, "r");
    
    printf("t\n");
	if(filePtr == NULL)
	{
		printf("Could not open file :( ");
		exit(-1);
	}
    
	fscanf(filePtr, "%d %d", &numTerminals, &numNonTerminals);
    printf("%p", filePtr);
	while(fscanf(filePtr, "%c:%s\n", &head, body) == 2)
	{
        printf("in while\n");
		Production *production = (Production *)malloc(sizeof(Production));
		production->number = count+1;
		production->head = head;
		production->body = body;
		production->next = NULL;
		// printf("Head : %c\n", head);
		// printf("Body : %s\n", body);
		// printf("Number : %c\n", number);
		// printf("------------------------------------------");
		
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
    printf("in parse\n");
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

	flag = 0;
	while(1)
	{
		Alphabet *tmpPtr = headPtr;
		state  = getw(filePtr);
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
					node->action = (char *)buffer;
					node->next = NULL;
					addNode(tmpPtr, node);
				}
				tmpPtr = tmpPtr->next;
				count = 0;
			}
			else if (ch == '\n')
			{
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
