
typedef struct Production Production;
typedef struct Alphabet Alphabet;
typedef struct Node Node;

struct Production
{
	int number;
	char head;
	char * body;
	Production *next;
};

struct Alphabet
{
	char alphabet;
	Alphabet *next;
	Node *statesPtr;
};


struct Node
{
	int state;
	char *action;
	Node *next;
};


