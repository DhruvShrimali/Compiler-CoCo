/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE_ST 30
//creates hashtable to implement symbol table

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
struct KeyValueST *create_pairST(const char *key, struct TokenFieldsST value) {
  struct KeyValueST *pair =
      (struct KeyValueST *)malloc(sizeof(struct KeyValueST));
  if (!pair) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }
  pair->key = strdup(key);
  pair->value = value;
  pair->next = NULL;
  return pair;
}

// Function to calculate the hash value for a given key
int hashST(const char *key) {
  unsigned long hash = 5381;
  int c;
  while ((c = *key++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % TABLE_SIZE_ST;
}

// Function to insert a key-value pair into the hash table
void insertST(struct HashTableST *ht, const char *key,
              struct TokenFieldsST value) {
  int index = hashST(key);
  struct KeyValueST *pair = create_pairST(key, value);
  // Insert at the beginning of the linked list
  pair->next = ht->table[index];
  ht->table[index] = pair;
}

// Function to retrieve the value associated with a key from the hash table
struct TokenFieldsST getST(struct HashTableST *ht, const char *key) {
  int index = hashST(key);
  struct KeyValueST *pair = ht->table[index];
  while (pair != NULL) {
    if (strcmp(pair->key, key) == 0)
      return pair->value;
    pair = pair->next;
  }
  // Key not found, return empty TokenFields
  struct TokenFieldsST empty_fields = {0};
  return empty_fields;
}

// Function to print the hash table
void print_tableST(struct HashTableST *ht) {
  printf("Hash Table:\n");
  for (int i = 0; i < TABLE_SIZE_ST; ++i) {
    struct KeyValueST *pair = ht->table[i];
    if (pair) {
      printf("Index %d: ", i);
      while (pair) {
        printf("(%s, token=%s, line_no=%d) -> ", pair->key, pair->value.token,
               pair->value.line_no);
        pair = pair->next;
      }
      printf("NULL\n");
    }
  }
}

// Function to free memory allocated for the hash table
void free_tableST(struct HashTableST *ht) {
  for (int i = 0; i < TABLE_SIZE_ST; ++i) {
    struct KeyValueST *pair = ht->table[i];
    while (pair) {
      struct KeyValueST *temp = pair;
      pair = pair->next;
      free(temp->key);
      // free(temp->value.lexeme);
      free(temp);
    }
  }
  free(ht);
}

void inititalizeTableST(struct HashTableST *ht) {
  for (int i = 0; i < TABLE_SIZE_ST; ++i)
    ht->table[i] = NULL;
  struct TokenFieldsST fields;

  fields.token = "TK_WITH";
  fields.line_no = -1;
  insertST(ht, "with", fields);

  fields.token = "TK_PARAMETERS";
  fields.line_no = -1;
  insertST(ht, "parameters", fields);

  fields.token = "TK_END";
  fields.line_no = -1;
  insertST(ht, "end", fields);

  fields.token = "TK_WHILE";
  fields.line_no = -1;
  insertST(ht, "while", fields);

  fields.token = "TK_UNION";
  fields.line_no = -1;
  insertST(ht, "union", fields);

  fields.token = "TK_ENDUNION";
  fields.line_no = -1;
  insertST(ht, "endunion", fields);

  fields.token = "TK_DEFINETYPE";
  fields.line_no = -1;
  insertST(ht, "definetype", fields);

  fields.token = "TK_AS";
  fields.line_no = -1;
  insertST(ht, "as", fields);

  fields.token = "TK_TYPE";
  fields.line_no = -1;
  insertST(ht, "type", fields);

  fields.token = "TK_MAIN";
  fields.line_no = -1;
  insertST(ht, "_main", fields);

  fields.token = "TK_GLOBAL";
  fields.line_no = -1;
  insertST(ht, "global", fields);

  fields.token = "TK_PARAMETER";
  fields.line_no = -1;
  insertST(ht, "parameter", fields);

  fields.token = "TK_LIST";
  fields.line_no = -1;
  insertST(ht, "list", fields);

  fields.token = "TK_INPUT";
  fields.line_no = -1;
  insertST(ht, "input", fields);

  fields.token = "TK_OUTPUT";
  fields.line_no = -1;
  insertST(ht, "output", fields);

  fields.token = "TK_INT";
  fields.line_no = -1;
  insertST(ht, "int", fields);

  fields.token = "TK_REAL";
  fields.line_no = -1;
  insertST(ht, "real", fields);

  fields.token = "TK_ENDWHILE";
  fields.line_no = -1;
  insertST(ht, "endwhile", fields);

  fields.token = "TK_IF";
  fields.line_no = -1;
  insertST(ht, "if", fields);

  fields.token = "TK_THEN";
  fields.line_no = -1;
  insertST(ht, "then", fields);

  fields.token = "TK_ENDIF";
  fields.line_no = -1;
  insertST(ht, "endif", fields);

  fields.token = "TK_READ";
  fields.line_no = -1;
  insertST(ht, "read", fields);

  fields.token = "TK_WRITE";
  fields.line_no = -1;
  insertST(ht, "write", fields);

  fields.token = "TK_RETURN";
  fields.line_no = -1;
  insertST(ht, "return", fields);

  fields.token = "TK_CALL";
  fields.line_no = -1;
  insertST(ht, "call", fields);

  fields.token = "TK_RECORD";
  fields.line_no = -1;
  insertST(ht, "record", fields);

  fields.token = "TK_ENDRECORD";
  fields.line_no = -1;
  insertST(ht, "endrecord", fields);

  fields.token = "TK_ELSE";
  fields.line_no = -1;
  insertST(ht, "else", fields);
}