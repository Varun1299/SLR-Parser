
typedef struct Production Production;

struct Production{
	int number;
	char head;
	char * body;
	Production *next;
};

