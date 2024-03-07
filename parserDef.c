/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 400
#define CONSTANT 30

// Used for first, follow and parse table
// Structure for the set associated with each token type
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
struct KeyValue *create_pair(const char *key, struct ValueFields value) {
  struct KeyValue *pair = (struct KeyValue *)malloc(sizeof(struct KeyValue));
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
int hash(const char *key) {
  unsigned long hash = 5381;
  int c;
  while ((c = *key++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % TABLE_SIZE;
}

// Function to insert a key-value pair into the hash table
void insert(struct HashTable *ht, const char *key, struct ValueFields value) {
  int index = hash(key);
  struct KeyValue *pair = create_pair(key, value);
  // Insert at the beginning of the linked list
  pair->next = ht->table[index];
  ht->table[index] = pair;
}

// Function to retrieve the value associated with a key from the hash table
struct ValueFields get(struct HashTable *ht, const char *key) {
  int index = hash(key);
  struct KeyValue *pair = ht->table[index];
  while (pair != NULL) {
    if (strcmp(pair->key, key) == 0)
      return pair->value;
    pair = pair->next;
  }
  // Key not found, return empty TokenFields
  struct ValueFields empty_fields = {0};
  return empty_fields;
}

bool checkTerminal(struct HashTable *ht, const char *key,
                   const char *terminal) {
  int index = hash(key);
  struct KeyValue *pair = ht->table[index];
  while (pair != NULL) {
    if (strcmp(pair->key, key) == 0) {
      int i = 0;
      while (pair->value.name[i] != NULL) {
        if (strcmp(pair->value.name[i], terminal) == 0)
          return true;
        i++;
      }
      return false;
    } else
      pair = pair->next;
  }
  return false;
}

void update(struct HashTable *ht, const char *key, struct ValueFields value) {
  int index = hash(key);
  struct KeyValue *pair = ht->table[index];
  while (pair != NULL) {
    if (strcmp(pair->key, key) == 0) {
      pair->value = value; // Update the value fields
      return;
    }
    pair = pair->next;
  }
  // Key not found, do nothing
}

int insertTerm(struct HashTable *ht, const char *key, const char *Terminal) {
  struct ValueFields fields = get(ht, key);
  if (fields.name[0] == NULL) {
    // printf("Could not find %s\n", key);
    fields.num = 1;
    char *string = (char *)malloc(sizeof(char) * strlen(Terminal));
    string = strdup(Terminal);
    fields.name[0] = string;
    insert(ht, key, fields);
    return 1;
  } else {
    if (checkTerminal(ht, key, Terminal) == false) {
      // printf("Did not find %s in %s\n", Terminal, key);
      int index = fields.num;
      fields.name[index] = strdup(Terminal);
      fields.num = index + 1;
      update(ht, key, fields);
      return 1;
    } else {
      return 0;
    }
  }
}

int insertRuleTerm(struct HashTable *ht, const char *key, const char *Terminal) {
  struct ValueFields fields = get(ht, key);
  if (fields.name[0] == NULL) {
    // printf("Could not find %s\n", key);
    fields.num = 1;
    char *string = (char *)malloc(sizeof(char) * strlen(Terminal));
    string = strdup(Terminal);
    fields.name[0] = string;
    insert(ht, key, fields);
    return 1;
  } else {
    int index = fields.num;
    fields.name[index] = strdup(Terminal);
    fields.num = index + 1;
    update(ht, key, fields);
  }
}

// Function to print the hash table
void print_table(struct HashTable *ht) {
  printf("Hash Table:\n");
  for (int i = 0; i < TABLE_SIZE; ++i) {
    struct KeyValue *pair = ht->table[i];
    if (pair) {
      printf("Index %d: ", i);
      while (pair) {
        printf("%s:{", pair->key);
        int i = 0;
        while (pair->value.name[i] != NULL) {
          printf("%s ", pair->value.name[i]);
          i++;
        }
        printf("} -> ");
        pair = pair->next;
      }
      printf("NULL\n");
    }
  }
}

// Function to free memory allocated for the hash table
void free_table(struct HashTable *ht) {
  for (int i = 0; i < TABLE_SIZE; ++i) {
    struct KeyValue *pair = ht->table[i];
    while (pair) {
      struct KeyValue *temp = pair;
      pair = pair->next;
      free(temp->key);
      // free(temp->value.lexeme);
      free(temp);
    }
  }
  free(ht);
}

void inititalizeTable(struct HashTable *ht) {
  for (int i = 0; i < TABLE_SIZE; ++i)
    ht->table[i] = NULL;
  struct ValueFields fields = {0};
}