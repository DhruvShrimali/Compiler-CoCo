/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include "TD.h"
#include "parserDef.h"
#include "grammarParser.h"
#include "lexer.h"
#include "parseTable.h"
#include "parseTree.h"
#include "stack.h"
#include "lexerDef.h"
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

PNode *Parse(char *filename, struct HashTable *ParseTable,struct HashTable *FollowSet) { //logic for parsing
  bool er=false;
  int erLine=0;
  char buffer[BUFFER_SIZE];
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file.\n");
  }
  readbuf1(file, buffer);
  readbuf2(file, buffer);
  int l_num = 1;
  int *line_number = &l_num;
  int x = 0;          // forward counter
  int y = 0;          // backward counter
  int *forward = &x;  // forward pointer
  int *backward = &y; // backward pointer
  bool flag=false;

  struct HashTableST *ht =
      (struct HashTableST *)malloc(sizeof(struct HashTableST)); // Make symbol table
  if (!ht) {
    perror("Memory allocation failed");
    exit(-1);
  }
  inititalizeTableST(ht); // Initialize symbol table
  Stack stack; 
  // generate node for <program>
  initialize(&stack);
  PNode *ParseTree = createNode("<program>"); //initialze parsetree
  push(&stack, "<program>", ParseTree); //initialze start symbol

  while (buffer[*backward] != '\0') {
    if (buffer[*backward] == '%') {// Code to skip comments
      *forward = ((*forward) + 1) % BUFFER_SIZE;
      while (buffer[*forward] != '\n') {
        checkForBuffer(forward, backward, buffer, file);
        *forward = ((*forward) + 1) % BUFFER_SIZE;
        (*backward) = (*forward);
      }
      *forward = ((*forward) + 1) % BUFFER_SIZE;
      checkForBuffer(forward, backward, buffer, file);
      (*backward) = (*forward);
      (*line_number)++;
      continue;
    }

    struct TokenInfo token =
        getNextToken(buffer, forward, backward, line_number, ht); //getting token stream
      if(strcmp(token.token, "ERROR")==0){
          printf("Line %d : Error: Unknown pattern <",token.lineNo);
          printf("%s", token.lexeme);
          printf(">\n");
      }
      else if(strcmp(token.token, "LONG_ERROR")==0){
          printf("Line %d : Error: Variable Identifier is longer than the prescribed length of 20 characters.\n",token.lineNo);
      }
      else if(strcmp(token.token, "UNKNOWN")==0){
          printf("Line %d : Error: Unknown symbol <", token.lineNo);
          printf("%c>\n", buffer[*backward]);
      }
      else if(strcmp(token.token, "NOTHING")==0);
    else {
      //Within this else brackeet we have the logic for making the parse table
      //each time we exit from this else and re-enter we will have next token
      PNode *currentNode = peekAdd(&stack);
      while (1) {
        char *Token = token.token; //getting current token
        int line = token.lineNo;  //line number
        char *lexeme = token.lexeme; //lexeme
        int intvalue = 0;
        float fvalue = 0.0;
        if (strcmp(Token, "TK_NUM") == 0) {
          intvalue = token.IntValue; //int value in case of integer token
        } else if (strcmp(Token, "TK_RNUM") == 0) {
          fvalue = token.FloatValue; //float value for float token
        }
        //Check top of the stack first:
        if (isTerminal(peek(&stack))) {
          //Case: Top of the stack is a terminal
          //strcmp(peek(&stack) = name of the Terminal on top of stack
          if (strcmp(peek(&stack),"eps") == 0) {
              VNode *temp = createVNode(0, line, 0.0, "eps");
              addVNode(currentNode, temp);
              pop(&stack); //when top is epsilon
              if (isEmpty(&stack)) {
                  printf("Parse Tree Generated\n");
                  return ParseTree;
              }
              currentNode=peekAdd(&stack);
              er=false;
          }
          else if (strcmp(peek(&stack), Token) == 0) { //when top of stack matches
            if(strcmp(peek(&stack), "$") == 0){ //end of parsing
              pop(&stack);
              if (isEmpty(&stack)) {
                //printf("Parse Tree Generated\n");
                return ParseTree;
              }
              er=false;
              break;
            }
            else{
              VNode *temp = createVNode(intvalue, line, fvalue, lexeme); //when top of stack is not end
              addVNode(peekAdd(&stack), temp);
              pop(&stack);
              er=false;
              break;
            }
          } else { //error handling in case of terminal mis-match
              if (strcmp(peek(&stack),"$") == 0) {
                printf("Line %d Error: Stack emptied before input finished. Code succesfully compiled till line: %d, Parse-Tree generated.\n",line,line);
              }
              else{
                if(strcmp(Token,"$")==0){ 
                  printf("Line %d Error: Panic mode error recovery is not possible. Partial Parse-Tree formed.\n",line);
                  while(strcmp(peek(&stack),"$")!=0){
                    PNode* tempNode=peekAdd(&stack);
                    VNode *temp = createVNode(0, line, 0.0, "ERROR");
                          addVNode(tempNode, temp);
                          pop(&stack);
                          currentNode=peekAdd(&stack);
                  }
                  pop(&stack);//stack is empty
                  return ParseTree;
                } 
                if(!er){
                  printf("Line %d Error: The token %s for lexeme %s does not match with expected token %s\n",line,Token,lexeme,stack.top->data);}
                er=true;
              }
            if(er && strcmp(Token,"TK_SEM")==0){
              er=false;
              pop(&stack);
            }
              break;// skipping tokens until a match is found or we reach end of the line i.e, TK_SEM
          }
        } 
        else { 
          //Case: Non-terminal on top of the stack
          char *key = (char *)malloc((strlen(peek(&stack)) + strlen(Token) + 1) * sizeof(char));
          strcpy(key, peek(&stack));
          strcat(key, Token); 
          struct ValueFields fields = get(ParseTable, key); //initializing
          if (fields.name[0] != NULL) // means key is in hash table i.e found corresponding rule
          {
            PNode *parent = peekAdd(&stack);
            pop(&stack);
            // push corresponding rules onto stack in reverse order
            int num = fields.num;
            char **rule = fields.name;
            PNode *children[num];
            for (int i = num - 1; i >= 0; i--) {
              PNode *temp = createNode(rule[i]);
              children[i] = temp;
              push(&stack, rule[i], temp);
            }
            for (int i = 0; i < num; i++) {
              addChild(currentNode, children[i]);
            }
            currentNode=peekAdd(&stack);
          } 
          else {//panic recovery mode
            while(!checkTerminal(FollowSet,currentNode->name,Token)){ //sync set(follow set) is checked with every token till match
              if(strcmp(Token,"$")){
                printf("Line %d Error: Panic mode error recovery is not possible. Partial Parse-Tree formed.\n",line);
                while(strcmp(peek(&stack),"$")!=0){
                  PNode* tempNode=peekAdd(&stack);
                  VNode *temp = createVNode(0, line, 0.0, "ERROR");
                  addVNode(tempNode, temp);
                  pop(&stack);
                  currentNode=peekAdd(&stack);
                }
                pop(&stack);//stack is empty
                //printf("returning parse tree\n");
                return ParseTree;
              }
              token =getNextToken(buffer, forward, backward, line_number, ht);
                if(strcmp(token.token, "ERROR")==0){
                    printf("Line %d : Error: Unknown pattern <",token.lineNo);
                    printf("%s", token.lexeme);
                    printf(">\n");
                }
                else if(strcmp(token.token, "LONG_ERROR")==0){
                    printf("Line %d : Error: Variable Identifier is longer than the prescribed length of 20 characters.\n",token.lineNo);
                }
                else if(strcmp(token.token, "UNKNOWN")==0){
                    printf("Line %d : Error: Unknown symbol <", token.lineNo);
                    printf("%c>\n", buffer[*backward]);
                }
                else if(strcmp(token.token, "NOTHING")==0);
              else{ // Skip tokens until we find a token that is present in the Follow set of current non-terminal
                  ;
              }
              checkForBuffer(forward, backward, buffer, file);
              *forward = ((*forward) + 1) % BUFFER_SIZE;
              (*backward) = (*forward);
              if (buffer[*backward] == '\0' && !flag) {
                buffer[*backward] = '$';
                buffer[(*backward)+1]='\0';
                flag=true;
              }
            }
            PNode* tempNode=peekAdd(&stack); //top of stack matches token
            VNode *temp = createVNode(0, line, 0.0, "ERROR");
            addVNode(tempNode, temp);
            pop(&stack);//pop stack
            currentNode=peekAdd(&stack);
            continue;
          }
        }
      }
    }
    checkForBuffer(forward, backward, buffer, file); // Check if buffer reload is required
    *forward = ((*forward) + 1) % BUFFER_SIZE; // Fowrard pointer increment
    (*backward) = (*forward); // Assign forward pointer to backward
    if (buffer[*backward] == '\0' && !flag) {// Code to add $ to buffer for proper working of parser stack
      buffer[*backward] = '$';
      buffer[(*backward)+1]='\0';
      flag=true;
    }
  } // end of while loop
          
  fclose(file);// close file reader
  freeStack(&stack);// parser stack is freed
  return ParseTree;
}


void printParseNode(PNode *node, PNode *parent, FILE* file){ //print parse node 
    if(node->childNo != 0) //helper function fro print parse tree
        printParseNode(node->children[0], node, file);

    if(node==NULL){
        return;
    }

    if(node->childNo == 0){
        if(node->value ==NULL){
            fprintf(file,"VNode not found for %s\n", node->name);
            return;
        }
        fprintf(file,"%22s", node->value->lexeme);
    }
    else
        fprintf(file,"%22s", "----");

    fprintf(file," %30s", node->name);

    if(node->childNo == 0) 
        fprintf(file," %3d", node->value->line_no);
    else
        fprintf(file, " ---");

    fprintf(file," %30s", node->name);

    if(strcmp(node->name, "TK_NUM")==0){
        fprintf(file," %10d", node->value->intValue);
    }
    else if(strcmp(node->name, "TK_RNUM")==0){
        fprintf(file," %10f", node->value->floatValue);
    }
    else{
        fprintf(file,"%*c", 11, ' ');
    }

    fprintf(file," %30s", parent->name);

    if(node->childNo == 0){
        fprintf(file," yes\n");
    }
    else{
        fprintf(file,"  no ");
        fprintf(file,"%s\n", node->name);
    }

    if(node->childNo > 1){
        for(int i=1; i<node->childNo; i++){
            printParseNode(node->children[i], node, file);
        }
    }

}

void printParseTree(PNode *ParseTree, char* filename){ //print parse tree in inorder
    FILE *file = fopen(filename, "w+");
    PNode *node= ParseTree;
    if(node->childNo != 0)
        printParseNode(node->children[0], node, file); //print first child

    if(node==NULL){
        return;
    }

    if(node->childNo == 0)  //case leaf
        fprintf(file, "%22s", node->value->lexeme);
    else
        fprintf(file, "%22s", "----");

    fprintf(file, " %30s", node->name);

    if(node->childNo == 0) 
        fprintf(file, " %3d", node->value->line_no);
    else
        fprintf(file," ---");

    fprintf(file ," %30s", node->name);

    if(strcmp(node->name, "TK_NUM")==0){
        fprintf(file, " %10d", node->value->intValue);
    }
    else if(strcmp(node->name, "TK_RNUM")==0){
        fprintf(file, " %10f", node->value->floatValue);
    }
    else{
        fprintf(file, "%*c", 11, ' ');
    }

    fprintf(file, " %30s", "----");

    if(node->childNo == 0){
        fprintf(file," yes\n");
    }
    else{
        fprintf(file, "  no ");
        fprintf(file, "%s\n", node->name);
    }

    if(node->childNo > 1){
        for(int i=1; i<node->childNo; i++){
            printParseNode(node->children[i], node, file);
        }
    }
    fclose(file);
}