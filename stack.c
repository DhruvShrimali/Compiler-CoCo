/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parseTree.h"

// Defines stack strcture for parser
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
void push(Stack* stack, char *data, struct PNode *node) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    newNode->node = node;
    stack->top = newNode;
}


// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to pop an element from the stack
void pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
    }
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}

// Function to display the top element of the stack
char* peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return NULL; // Returning NULL
    }
    return stack->top->data;
}

PNode* peekAdd(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return NULL; // Returning NULL
    }
    return stack->top->node;
}

// Function to initialize the stack
void initialize(Stack* stack) {
    stack->top = NULL;
    push(stack, "$", NULL); // Pushing the initial symbol onto the stack
}

// Function to display the stack elements
void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    Node* current = stack->top;
    printf("Stack: ");
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free memory allocated for the stack nodes
void freeStack(Stack* stack) {
    Node* current = stack->top;
    Node* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL; // Reset top pointer after freeing all nodes
}