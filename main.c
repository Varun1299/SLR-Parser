

#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "reader.h"
#include "slr_parse.c"
#include "stack.h"

int main(int argc, char const *argv[])
{
	//char productionFile[100], parseTableFile[100];
    printf("Enter file name of the file containing the productions :\n");
	//scanf("%s", productionFile);

    char *productionFile = "assignment2-sample-grammar1.txt";

    printf("Yo \n");
    Production *productions = productionFileReader(productionFile);
    printf("Enter file name of the file containing the parse table :\n");
	//scanf( "%s", parseTableFile);

	char *parseTableFile = "assignment2-sample-parsetable1.csv";

	Alphabet *parseTable = parseTableReader(parseTableFile);
	int root_state = 0;
	char root_symbol = '$';
	struct stackNode* root = newNode(root_state, root_symbol); 

	char inputString[100];
	while(1)
	{
		printf("Provide Input:\n");
		scanf("%s", inputString);
		if (inputString[0] == '\0') {break;}
		for(int i = 0; i < strlen(inputString); i++)
		{
			parse_char(inputString[i], &root, productions, parseTable);
		}
	}

	return 0;
}


