/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#ifndef PARSERDEF_H
#define PARSERDEF_H
#include <stdbool.h>
#define TABLE_SIZE 400
#define CONSTANT 30

// Structure for the first set associated with each token type
struct ValueFields {
  char *name[CONSTANT];
  int num;
};

// Structure for a key-value pair
struct KeyValue {
  char *key;
  struct ValueFields value;
  struct KeyValue *next;
};

// Structure for the hash table
struct HashTable {
  struct KeyValue *table[TABLE_SIZE];
};

// Function to create a new key-value pair
struct KeyValue *create_pair(const char *key, struct ValueFields value);

// Function to calculate the hash value for a given key
int hash(const char *key);

// Function to insert a key-value pair into the hash table
void insert(struct HashTable *ht, const char *key, struct ValueFields value);

// Function to retrieve the value associated with a key from the hash table
struct ValueFields get(struct HashTable *ht, const char *key);

// Function to check if a terminal is present in values of the the key
bool checkTerminal(struct HashTable *ht, const char *key, const char *terminal);

// Function to update the value of a key in the hash table
void update(struct HashTable *ht, const char *key, struct ValueFields value);

// Function to insert terminal into value of a key in the hash table
int insertTerm(struct HashTable *ht, const char *key, const char *Terminal);

// Function to insert rule terminal into value of a key in the hash table
int insertRuleTerm(struct HashTable *ht, const char *key, const char *Terminal);

// Function to print the hash table
void print_table(struct HashTable *ht);

// Function to free memory allocated for the hash table
void free_table(struct HashTable *ht);

// Function to initialize the hash table
void inititalizeTable(struct HashTable *ht);

#endif