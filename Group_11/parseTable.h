/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#ifndef PARSETABLE_H
#define PARSETABLE_H
#include "parserDef.h"
#include "grammarParser.h"

void insertIntoTable(struct HashTable *ParseTable, char *key, Symbol *rule,
																					int rules);

void createParseTable(Grammar *G, struct HashTable *ParseTable,
																							struct HashTable *FirstSet,
																							struct HashTable *FollowSet);

#endif