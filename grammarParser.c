/*
Rudra Jewalikar - 2021A7PS0450P
Dhruv Shrimali - 2021A7PS0008P
Salil Godbole - 2021A7PS2004P
Shyam Raghavan - 2021A7PS0013P
Sarthak Sharma - 2021A7PS2535P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parserDef.h"
#define MAX_LENGTH 40
#define MAX_RULELENGTH 30
#define MAX_RULES 200
#define MAX_SYMBOLS 200

// Structure to represent a symbol (terminal or non-terminal)
typedef struct {
		char name[MAX_LENGTH];
} Symbol;

// Structure to represent a production rule
typedef struct {
		Symbol left;                  // Left-hand side non-terminal
		Symbol right[MAX_RULELENGTH]; // Right-hand side symbols
		int numSymbols;               // Number of symbols on the right hand side
} ProductionRule;

// Structure to represent the grammar
typedef struct {
		Symbol nonTerminals[MAX_SYMBOLS]; // Non-terminal symbols
		Symbol terminals[MAX_SYMBOLS];    // Terminal symbols
		ProductionRule rules[MAX_RULES];  // Production rules
		int numNonTerminals;              // Number of non-terminals
		int numTerminals;                 // Number of terminals
		int numRules;                     // Number of production rules
} Grammar;

typedef struct {
		Symbol Nonterminal;
		char *name[MAX_SYMBOLS];
} first;

// Function to initialize grammar
void initializeGrammar(Grammar *G) {
  G->numNonTerminals = 0;
  G->numTerminals = 0;
  G->numRules = 0;
}

// Function to add a non-terminal symbol to the grammar
void addNonTerminal(Grammar *G, const char *name) {
  for (int i = 0; i < G->numNonTerminals; i++) {
    if (strcmp(G->nonTerminals[i].name, name) == 0)
      return;
  }
  if (G->numNonTerminals < MAX_SYMBOLS) {
    strcpy(G->nonTerminals[G->numNonTerminals].name, name);
    G->numNonTerminals++;
  } else {
    printf("Maximum number of non-terminals reached.\n");
  }
}

// Function to add a terminal symbol to the grammar
void addTerminal(Grammar *G, const char *name) {
  for (int i = 0; i < G->numTerminals; i++) {
    if (strcmp(G->terminals[i].name, name) == 0)
      return;
  }
  if (G->numTerminals < MAX_SYMBOLS) {
    strcpy(G->terminals[G->numTerminals].name, name);
    G->numTerminals++;
  } else {
    printf("Maximum number of terminals reached.\n");
  }
}

// Function to add a production rule to the grammar
void addProductionRule(Grammar *G, char *left, char *right[], int numSymbols) {
  if (G->numRules < MAX_RULES) {
    strcpy(G->rules[G->numRules].left.name, left);
    G->rules[G->numRules].numSymbols = numSymbols;
    int i = 0;
    for (i = 0; i < numSymbols; i++) {
      strcpy(G->rules[G->numRules].right[i].name, right[i]);
    }
    G->numRules++;
  } else {
    printf("Maximum number of production rules reached.\n");
  }
}
void parseGrammarFromFile(Grammar *G, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file.\n");
  }
  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    char *lin = strtok(line, "\n");
    char *token = strtok(lin, " ");
    if (token == NULL)
      continue;
    addNonTerminal(G, token);
    char *ruleLHS = token;
    while (1) {
      char *ruleRHS[MAX_SYMBOLS];
      int i = 0;
      while ((token = strtok(NULL, " ")) != NULL) {
        if (token[0] == 'T' | token[0] == 'e') {
          addTerminal(G, token);
          ruleRHS[i] = token;
          i++;
        } else if (token[0] == '<') {
          addNonTerminal(G, token);
          ruleRHS[i] = token;
          i++;
        } else if (token[0] == '|' || token[0] == '\n') {
          addProductionRule(G, ruleLHS, ruleRHS, i);
          break;
        }
      }
      if (token == NULL) {
        addProductionRule(G, ruleLHS, ruleRHS, i);
        break;
      }
    }
  }
}

// Function to visualize the grammar
void visualizeGrammar(const Grammar *G) {
  printf("Grammar Visualization:\n");
  printf("---------------------\n");

  printf("Non-terminals:\n");
  for (int i = 0; i < G->numNonTerminals; i++) {
    printf("%d)%s\t", i + 1, G->nonTerminals[i].name);
  }
  printf("\n");

  printf("Terminals:\n");
  for (int i = 0; i < G->numTerminals; i++) {
    printf("%d)%s\t", i + 1, G->terminals[i].name);
  }
  printf("\n");

  printf("Production rules:\n");
  for (int i = 0; i < G->numRules; i++) {
    printf("%d) %s ==> ", i + 1, G->rules[i].left.name);
    for (int j = 0; j < G->rules[i].numSymbols; j++) {
      printf("%s ", G->rules[i].right[j].name);
    }
    printf("\n");
  }
}

int isTerminal(char *name) {
  if (name[0] == 'T' || name[0] == 'e' || name[0] == '$')
    return 1;
  else if (name[0] == '<')
    return 0;
  else {
    //printf("Invalid token: #%s#\n", name);
    return 0;
  }
}

int findNtInFirst(char *Nt, Grammar *G, first *F) {
  for (int i = 0; i < G->numNonTerminals; i++) {
    if (strcmp(F[i].Nonterminal.name, Nt) == 0) {
      return i;
    }
  }
  printf("Error: Nonterminal %s not found in first set.\n", Nt);
  return -1;
}

int insertFtoF(struct HashTable *FirstSet, const char *key1, const char *key2) {
  int change = 0;
  struct ValueFields fields = get(FirstSet, key2);
  int limit = fields.num;
  for (int i = 0; i < limit; i++) {
    if (isTerminal(fields.name[i]) && strcmp(fields.name[i], "eps") != 0) {
      if (checkTerminal(FirstSet, key1, fields.name[i]) == 0) {
        insertTerm(FirstSet, key1, fields.name[i]);
        change = 1;
      } else
        continue;
    } else
      continue;
  }
  return change;
}

int insertFirstToFollow(struct HashTable *FirstSet, struct HashTable *FollowSet,
                        const char *key1, const char *key2) {
  int change = 0;
  struct ValueFields fields = get(FirstSet, key2);
  int limit = fields.num;
  for (int i = 0; i < limit; i++) {
    if (isTerminal(fields.name[i]) && strcmp(fields.name[i], "eps") != 0) {
      if (checkTerminal(FollowSet, key1, fields.name[i]) == 0) {
        insertTerm(FollowSet, key1, fields.name[i]);
        change = 1;
      } else
        continue;
    } else
      continue;
  }
  return change;
}

void computeFirstSets(Grammar *G, struct HashTable *FirstSet) {
  // We will iterate over all the grammer rules one by one in each pass
  // adding all the directly derivable terminals to appropripate first sets aka
  // first pass
  for (int i = 0; i < G->numRules; i++) {
    ProductionRule rule = G->rules[i];
    Symbol left = rule.left;
    Symbol firstSymbol = rule.right[0];
    // If first symbol is a terminal or epsilon, add it to first set of left
    // non-terminal
    if (isTerminal(firstSymbol.name)) {
      insertTerm(FirstSet, left.name, firstSymbol.name);
    }
  }
  int change = 1;
  while (change) {
    // print_table(FirstSet);
    change = 0;
    for (int i = 0; i < G->numRules; i++) {
      int k = 0;
      ProductionRule rule = G->rules[i];
      Symbol left = rule.left;
      Symbol firstSymbol = rule.right[k];
      while (1) {
        if (!isTerminal(firstSymbol.name)) {
          if (insertFtoF(
                  FirstSet, left.name,
                  firstSymbol
                      .name)) { // adding first set of right symbols to first
                                // set of left non-terminal. insertFirst takes
                                // care of the duplicates and return if any
                                // changes were made in first set or not
            change = 1;
          }
          if (checkTerminal(
                  FirstSet, firstSymbol.name,
                  "eps")) { // checking for epsilon in First set of Right Symbol
            if (k >= rule.numSymbols) {
              insertFtoF(FirstSet, left.name, "eps");
              break;
            }
            firstSymbol = rule.right[++k];
          } else {
            break;
          }
        } else {
          if (isTerminal(firstSymbol.name)) {
            if (insertTerm(FirstSet, left.name, firstSymbol.name)) {
              change = 1;
            }
          }
          break;
        }
      }
    }
  }
}

void initializeFollow(Grammar *G, struct HashTable *FollowSet) {
  for (int i = 0; i < G->numNonTerminals; i++) {
    if (strcmp(G->nonTerminals[i].name, "<program>") == 0) {
      insertTerm(FollowSet, G->nonTerminals[i].name, "$");
      break;
    }
  }
}

void computeFollowSets(Grammar *G, struct HashTable *FollowSet,
                       struct HashTable *FirstSet) {
  initializeFollow(G, FollowSet);
  // We will iterate over all the grammer rules one by one in each pass
  //  print_table(FollowSet);
  int change = 1;
  while (change) {
    change = 0;
    for (int i = 0; i < G->numRules; i++) {
      ProductionRule rule = G->rules[i];
      Symbol left = rule.left;
      Symbol firstSymbol;
      int j = 0;
      for (int j = 0; j < rule.numSymbols; j++) {
        firstSymbol = rule.right[j];
        if (!isTerminal(firstSymbol.name)) {
          for (int k = j + 1; k < rule.numSymbols; k++) {
            if (isTerminal(rule.right[k].name)) {
              if (insertTerm(FollowSet, firstSymbol.name, rule.right[k].name)) {
                change = 1;
              }
              break;
            } else if (!isTerminal(rule.right[k].name)) {
              if (insertFirstToFollow(FirstSet, FollowSet, firstSymbol.name,
                                      rule.right[k].name)) {
                change = 1;
              }
              if (checkTerminal(FirstSet, rule.right[k].name, "eps")) {
                if (k != rule.numSymbols - 1)
                  continue;
                else {
                  if (insertFtoF(FollowSet, firstSymbol.name, left.name)) {
                    change = 1;
                  }
                }
              } else {
                break;
              }
            }
          }
          if (j == rule.numSymbols - 1) {
            if (insertFtoF(FollowSet, firstSymbol.name, left.name)) {
              change = 1;
            }
          }
        }
      }
    }
  }
}

// Function to print first sets
void printFirstSets(const Grammar *G, const first *F) {
  printf("First Sets:\n");
  for (int i = 0; i < G->numNonTerminals; i++) {
    printf("First(%s): { ", G->nonTerminals[i].name);
    for (int j = 0; j < MAX_SYMBOLS; j++) {
      if (F[i].name[j] != NULL) {
        printf("%s ", F[i].name[j]);
      }
    }
    printf("}\n");
  }
}

void ComputeFirstAndFollowSets(Grammar *G, struct HashTable *FirstSet, struct HashTable *FollowSet){
    initializeGrammar(G);
    parseGrammarFromFile(G, "Grammar.txt");
    inititalizeTable(FirstSet);
    computeFirstSets(G, FirstSet);
    inititalizeTable(FollowSet);
    computeFollowSets(G, FollowSet, FirstSet);
}