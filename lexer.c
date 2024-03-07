/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include "TD.h"
#include "lexerDef.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readbuf1(FILE *file, char *buffer) {// Reads first half of buffer
  int count = 0;
  while (count < (BUFFER_SIZE / 2)) {
    if (fscanf(file, "%c", buffer + count) == EOF) {
      buffer[count] = '\0';
      break;
    }
    count++;
  }

}


void readbuf2(FILE *file, char *buffer) {// Reads second half of buffer
  int count = BUFFER_SIZE / 2;
  while (count < BUFFER_SIZE) {
    if (fscanf(file, "%c", buffer + count) == EOF) {
      buffer[count] = '\0';
      break;
    }
    count++;
  }
}

// Checks forward and backward pointer if buffer need to be filled
void checkForBuffer(int* i, int* j, char* buffer, FILE *file) {
    if ((*i) == BUFFER_SIZE -1 || ((*j) < BUFFER_SIZE && (*j) > BUFFER_SIZE / 2 && (*i) >= 0 && (*i) < BUFFER_SIZE / 2)) {
        readbuf2(file, buffer);
    } else if ((*i) == (BUFFER_SIZE / 2) -1 || ((*i) >= BUFFER_SIZE / 2 && (*i) < BUFFER_SIZE && (*j) > 0 && (*j) < BUFFER_SIZE / 2)) {
        readbuf1(file, buffer);
    }
}

// Prints on console the code without comments
void removeComments(char *testcaseFile){
    FILE *file = fopen(testcaseFile, "r");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if(ch=='%'){
            ch = fgetc(file);
            while(ch != '\n'){
                ch = fgetc(file);
            }
        }
        printf("%c", ch);
    }

    // Check for read error
    if (ferror(file)) {
        perror("Error reading from source file");
        fclose(file);
        return;
    }
    fclose(file);
}


void printTokenList(char *filename){
    char buffer[BUFFER_SIZE];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    readbuf1(file, buffer);
    readbuf2(file, buffer);
    int l_num=1; //line number
    int* line_number = &l_num; //line number pointer
    int x=0; //forward counter
    int y=0; //backward counter
    int *forward = &x; // forward pointer
    int *backward = &y; // backward pointer

    struct HashTableST *ht = (struct HashTableST*)malloc(sizeof(struct HashTableST));
    if (!ht) {
        perror("Memory allocation failed");
        exit(-1);
    }
    inititalizeTableST(ht);

    while(buffer[*backward]!='\0'){

        if(buffer[*backward] == '%'){// Code to ignore comment
            printf("Line No. %-8d Lexeme ",*line_number);
            printf("%-22s", "%");
            printf("Token %s\n", "TK_COMMENT");
            *forward = ((*forward)+1) % BUFFER_SIZE;
            while(buffer[*forward]!='\n'){// Ignores till new line character
                checkForBuffer(forward, backward, buffer, file);
                *forward = ((*forward)+1) % BUFFER_SIZE;
                (*backward)=(*forward);
            }
            *forward = ((*forward)+1) % BUFFER_SIZE;
            checkForBuffer(forward, backward, buffer, file);
            (*backward)=(*forward);
            (*line_number)++;
            continue;
        }

        struct TokenInfo token = getNextToken(buffer, forward, backward, line_number, ht);
        if(strcmp(token.token, "ERROR")==0){
            printf("Line No. %d : Error: Unknown pattern <",token.lineNo);
            printf("%s", token.lexeme);
            printf(">\n");
        }
        else if(strcmp(token.token, "LONG_ERROR")==0){
            printf("Line No. %d : Error: Variable Identifier is longer than the prescribed length of 20 characters.\n",token.lineNo);
        }
        else if(strcmp(token.token, "UNKNOWN")==0){
            printf("Line No. %d : Error: Unknown symbol <", token.lineNo);
            printf("%c>\n", buffer[*backward]);
        }
        else if(strcmp(token.token, "NOTHING")==0);
        else{// Pretty printing
            printf("Line No. %-8d Lexeme ",token.lineNo);
            printf("%-22s", token.lexeme);
            printf("Token %s\n", token.token);
        }
        checkForBuffer(forward, backward, buffer, file);
        *forward = ((*forward)+1) % BUFFER_SIZE;
        (*backward)=(*forward);
    }
    printf("\n");
    fclose(file);
    return;
}