#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "reader.h"
#include "slr_parse.c"
#include "stack.h"

int int main(int argc, char const *argv[])
{
	char productionFile[100], parseTableFile[100];
	scanf("Enter file name of the file containing the productions :\n %s\n", &productionFile);
	scanf("Enter file name of the file containing the parse table :\n %s\n", &parseTableFile);

	Production *productions = productionFileReader(&productionFile);
	Alphabet *parseTable = parseTableReader(&parseTableFile);
	int root_state = 0;
	char root_symbol = '$';
	struct stackNode* root = newNode(root_state, root_symbol); 

	char inputString[100];
	while(1)
	{
		printf("Provide Input:\n");
		scanf("%s", &input);
		if (input[0] == '\0') {break;}
		for(int i = 0; i < strlen(); i++)
		{
			parse_char(input[i], root, productions, parseTable);	
		}
	}

	return 0;
}