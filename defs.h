#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

typedef struct Productions{
    int number;
    char head;
    char body[256];
    struct Productions *next;
} Production;

typedef struct Nodes{
    int state;
    char action[100];
    struct Nodes *next;
} Node;

typedef struct Alphabets{
    char alphabet;
    struct Alphabets *next;
    Node *statesPtr;
} Alphabet;


//typedef struct DoubleStack DoubleStack;


typedef struct dataPair
{
	int state;
	char symbol;
} dataPair;

#endif
