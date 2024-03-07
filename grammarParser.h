/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#ifndef GRAMMARPARSER_H
#define GRAMMARPARSER_H
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
void initializeGrammar(Grammar *G);

// Function to add a non-terminal symbol to the grammar
void addNonTerminal(Grammar *G, const char *name);

// Function to add a terminal symbol to the grammar
void addTerminal(Grammar *G, const char *name);

// Function to add a production rule to the grammar
void addProductionRule(Grammar *G, char *left, char *right[], int numSymbols);

void parseGrammarFromFile(Grammar *G, const char *filename);

// Function to visualize the grammar
void visualizeGrammar(const Grammar *G);

int isTerminal(char *name);

int findNtInFirst(char *Nt, Grammar *G, first *F);

int insertFtoF(struct HashTable *FirstSet, const char *key1, const char *key2);

int insertFirstToFollow(struct HashTable *FirstSet, struct HashTable *FollowSet,
                        const char *key1, const char *key2);

void computeFirstSets(Grammar *G, struct HashTable *FirstSet);

void initializeFollow(Grammar *G, struct HashTable *FollowSet);

void computeFollowSets(Grammar *G, struct HashTable *FollowSet,
                       struct HashTable *FirstSet);

void printFirstSets(const Grammar *G, const first *F);

void ComputeFirstAndFollowSets(Grammar *G, struct HashTable *FirstSet,
                               struct HashTable *FollowSet);

#endif