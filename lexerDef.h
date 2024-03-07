/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#ifndef LEXER_DEF_H
#define LEXER_DEF_H
#define TABLE_SIZE_ST 30

// Structure for the fields associated with each token type
struct TokenFieldsST {
  char *token;
  int line_no;
};

// Structure for a key-value pair
struct KeyValueST {
  char *key;
  struct TokenFieldsST value;
  struct KeyValueST *next;
};

// Structure for the hash table
struct HashTableST {
  struct KeyValueST *table[TABLE_SIZE_ST];
};

// Function to create a new key-value pair
struct KeyValueST *create_pairST(const char *key, struct TokenFieldsST value);

// Function to calculate the hash value for a given key
int hashST(const char *key);

// Function to insert a key-value pair into the hash table
void insertST(struct HashTableST *ht, const char *key,
              struct TokenFieldsST value);

// Function to retrieve the value associated with a key from the hash table
struct TokenFieldsST getST(struct HashTableST *ht, const char *key);

// Function to print the hash table
void print_tableST(struct HashTableST *ht);

// Function to free memory allocated for the hash table
void free_tableST(struct HashTableST *ht);

void inititalizeTableST(struct HashTableST *ht);

#endif