/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#ifndef LEXER_H
#define LEXER_H
#include "TD.h"
#include "lexerDef.h"
#include <stdio.h>


//fills first half of buffer
void readbuf1(FILE *file, char *buffer);

//fills second half of buffer
void readbuf2(FILE *file, char *buffer);

//checks sing forward and backward pointer if filling buffer is needed
void checkForBuffer(int *i, int *j, char *buffer, FILE *file);

//writes original code without comments to destination file
void removeComments(char *testcaseFile);

//prints tokens to console of given code file
void printTokenList(char *filename);
#endif