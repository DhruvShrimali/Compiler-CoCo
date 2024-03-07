/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#ifndef TD_H
#define TD_H
#define BUFFER_SIZE 200
#include "lexerDef.h"

struct TokenInfo {
  char* token;
  char lexeme[22];
  int lineNo;
  int IntValue;
  float FloatValue;
};

//return next token from the buffer, also checks in symbol table
struct TokenInfo getNextToken(char *buffer, int *i, int *j, int *line_number,
struct HashTableST *ht);
#endif
