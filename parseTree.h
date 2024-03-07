/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#ifndef PARSETREE_H
#define PARSETREE_H
#define NO_OF_CHILDREN 9

typedef struct VNode{
    int intValue;
    int line_no;
    float floatValue;
    char *lexeme;
}VNode;

typedef struct PNode{
  char *name;
  int childNo;
  VNode *value;
  struct PNode *children[NO_OF_CHILDREN];
  // struct parseTreeNode *parent;
}PNode;

PNode * createNode(char *name);

VNode * createVNode(int intValue, int line_no, float floatValue, char *lexeme);

void addVNode(PNode *node, VNode *vNode);

void addChild(PNode *parent, PNode *child);

#endif