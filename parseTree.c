/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define NO_OF_CHILDREN 9

//Node for leaf nodes to store extra info
typedef struct VNode{
				int intValue;
				int line_no;
				float floatValue;
				char *lexeme;
}VNode;


//Normal tree node
typedef struct PNode{
		char *name;
		int childNo;
		VNode *value;
		struct PNode *children[NO_OF_CHILDREN];
		// struct parseTreeNode *parent;
}PNode;

PNode *createNode(char *name) {
  PNode *node = (PNode *)malloc(sizeof(PNode));
  node->name = (char *)malloc(sizeof(node->name));
  node->name = strdup(name);
  node->childNo = 0;
  for (int i = 0; i < NO_OF_CHILDREN; i++) {
    node->children[i] = NULL;
  }
  return node;
}

VNode *createVNode(int intValue, int line_no, float floatValue, char *lexeme) {
  VNode *vNode = (VNode *)malloc(sizeof(VNode));
  vNode->intValue = intValue;
  vNode->line_no = line_no;
  vNode->floatValue = floatValue;
  vNode->lexeme = (char *)malloc(sizeof(vNode->lexeme));
  vNode->lexeme = strdup(lexeme);
  return vNode;
}

void addChild(PNode *parent, PNode *child) {
  parent->children[parent->childNo] = child;
  parent->childNo = (parent->childNo) + 1;
}

void addVNode(PNode *node, VNode *value) {
  node->value = value;
  node->childNo = 0;
}