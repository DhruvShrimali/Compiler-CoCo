/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#ifndef STACK_H
#define STACK_H
#include "parseTree.h"
#include <stdbool.h>

// Define a structure for a node
typedef struct Node {
    char* data;
    struct PNode *node;
    struct Node* next;
} Node;

// Define a structure for the stack
typedef struct Stack {
    Node* top;
} Stack;

// Function to push an element onto the stack
void push(Stack* stack, char *data, struct PNode *node);

// Function to pop an element from the stack
void pop(Stack* stack);

// Function to display the top element of the stack
char* peek(Stack* stack);

// Function to return the address the top element of the stack
PNode* peekAdd(Stack* stack);

// Function to check if the stack is empty
bool isEmpty(Stack* stack);

// Function to display the stack elements
void display(Stack* stack);

// Function to free memory allocated for the stack nodes
void freeStack(Stack* stack);

// Function to initialize the stack
void initialize(Stack* stack);

#endif
