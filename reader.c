#include <stdio.h>
#include <stdlib.h>
#include "defs.h"


Production *productionFileReader(char *fileName)
{
	char head;
	char *body;
	FILE *filePtr;
	int numTerminals, numNonTerminals, count = 0;
	Production *headptr;
	Production *tailptr;
 

	filePtr = fopen(fileName, "r");
	if(filePtr == NULL)
	{
		printf("Could not open file :(");
		exit(-1);
	}

	fscanf(filePtr, "%d %d\n", &numTerminals, &numNonTerminals);

	while(fscanf(filePtr, "%c:%s\n", &head, body) == 2)
	{
		Production *production = (Production *)malloc(sizeof(Production));
		production->number = count+1;
		production->head = head;
		production->body = body;
		// printf("Head : %c\n", head);
		// printf("Body : %s\n", body);
		// printf("Number : %c\n", number);
		// printf("------------------------------------------");
		
		if(count == 0)
		{
		    headptr = production;
		    tailptr = production;
		}
		else
		{
			tailptr->next = production;
			tailptr = production;
		}
		count++;
	}
	return headptr;
}


int main(int argc, char const *argv[])
{
	
	return 0;
}
