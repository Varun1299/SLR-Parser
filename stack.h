#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "defs.h"

/* Implementation of stack using linked lists. */

/*Struct for a single node that's pushed into the stack
 next stores the pointer to the next node, pair is of type struct dataPair
 which stores the state and the symbol. stack_length stores the length of the
 stack till that entry*/

struct stackNode
{
    struct stackNode* next;
    struct dataPair pair;
    int stack_length;
};

/*Function used to make a new node. Takes two arguments state and symbol
 and returns a node*/

struct stackNode* newNode(int state, char symbol)
{
    struct stackNode* Node =
    (struct stackNode*) malloc(sizeof(struct stackNode));
    Node->pair.state = state;
    Node->pair.symbol = symbol;
    Node->next = NULL;
    return Node;
};

/*Used to check if root exists or not.*/

int isEmpty(struct stackNode *root)
{
    return !root;
}

/* Method to push elements to the stack. Takes the root, state, and symbol
 as inputs and updates the root*/

void push(struct stackNode** root, int state, char symbol)
{
    struct stackNode* Node = newNode(state, symbol);
    Node->next = *root;
    int prev_length = Node->next->stack_length;
    *root = Node;
    (*root)->stack_length = prev_length + 1;
    //printf("Pushed to stack\n");
}

/*Method used to pop elements from the stack.
 Returns a pointer to a struct of type dataPair that is popped out
 */

dataPair* pop(struct stackNode** root)
{
    if (isEmpty(*root)){
        printf("Stack is empty, cannot pop\n");
        return NULL;
    }
    struct stackNode* temp = *root;
    int prev_length = (*root)->stack_length;
    *root = (*root)->next;
    (*root)->stack_length = prev_length - 1;
    dataPair* popped = &temp->pair; //baadme dekhlenge
    free(temp);
    return popped;
}

#endif
