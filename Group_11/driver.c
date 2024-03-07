/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include "parser.h"
#include "TD.h"
#include "parserDef.h"
#include "grammarParser.h"
#include "lexer.h"
#include "parseTable.h"
#include "parseTree.h"
#include "stack.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Invalid number of arguments\n");
    return -1;
  }
  printf("(a) FIRST and FOLLOW set automated\n");
  printf("(c) Both lexical and syntax analysis modules implemented\n");
  printf("all modules compile\n");
  printf("modules work from testcases 1 to 6\n");
  printf("Extra testcase testcase7.txt added\n");
  clock_t start_time, end_time;
  double total_CPU_time, total_CPU_time_in_seconds;
  bool executed = false;

  while (1) {
    printf("\nPlease input your request: \n");
    printf("0: exit\n");
    printf("1: remove comments\n");
    printf("2: print token list\n");
    printf("3: verify syntactic correctness of code\n");
    printf("4: print time taken for step 3\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 0) {
      break;
    } else if (choice == 1) {
      printf("Comments removed file:\n");
      removeComments(argv[1]);
    } else if (choice == 2) {
      printf("Token list:\n");
      printTokenList(argv[1]);
    } else if (choice == 3) {
      start_time = clock();
      Grammar *G = (Grammar *)malloc(sizeof(Grammar));
      struct HashTable *FirstSet =
          (struct HashTable *)malloc(sizeof(struct HashTable));
      if (!FirstSet) {
        perror("Memory allocation failed");
        exit(-1);
      }

      struct HashTable *FollowSet =
          (struct HashTable *)malloc(sizeof(struct HashTable));
      if (!FirstSet) {
        perror("Memory allocation failed");
        exit(-1);
      }
      ComputeFirstAndFollowSets(G, FirstSet, FollowSet);
      struct HashTable *ParseTable =
          (struct HashTable *)malloc(sizeof(struct HashTable));
      createParseTable(G, ParseTable, FirstSet, FollowSet);
      free_table(FirstSet);
      
      PNode *tree = Parse(argv[1], ParseTable, FollowSet);
      printParseTree(tree, argv[2]);
      free_table(FollowSet);
      free_table(ParseTable);
      end_time = clock();
      executed = true;
        
    } else if (choice == 4) {
      if(executed){
        total_CPU_time = (double)(end_time - start_time);

        total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
        printf("Total CPU time: %lf clock ticks\n", total_CPU_time);
        printf("Total CPU time in seconds: %lf seconds\n", total_CPU_time_in_seconds);
      }
      else{
        printf("Please run step 3 first\n");
      }
      // Print both total_CPU_time and total_CPU_time_in_seconds
    }
  }
  return 1;
}