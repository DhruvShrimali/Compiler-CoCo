/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/
#ifndef PARSER_H
#define PARSER_H
#include "parseTree.h"
#include <stdio.h>

PNode *Parse(char *filename, struct HashTable *ParseTable, struct HashTable *FollowSet);

void printParseNode(PNode *node, PNode *parent, FILE* file);

void printParseTree(PNode *ParseTree, char* filename);
#endif