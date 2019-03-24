
typedef struct Production Production;
typedef struct Alphabet Alphabet;
typedef struct Node Node;
typedef struct DoubleStack DoubleStack;

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

struct DoubleStack
{
	int state;
	char symbol;
}
