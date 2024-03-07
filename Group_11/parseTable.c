/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include "parserDef.h"
#include "grammarParser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void insertIntoTable(struct HashTable *ParseTable, char *key, Symbol *rule,
                                                                                    int rules)   
{                               //helper function in order to insert rules into parsing table
    struct ValueFields check = get(ParseTable, key);
    if (check.name[0] != NULL){
        printf("Duplicate entries in table at key: %s\n", key);
        printf("%s ==> ", key);
        for (int i = 0; i < rules; i++){
             printf("%s ", rule[i].name);
        }
        printf("\n");
    }
    for (int i = 0; i < rules; i++)
	{
		insertRuleTerm(ParseTable, key, rule[i].name);
	}
	return;
        // key=left.name+firstSymbol.name
        // for the key we will have to insert the rule.
}

void createParseTable(Grammar *G, struct HashTable *ParseTable,struct HashTable *FirstSet,struct HashTable *FollowSet)
{
	inititalizeTable(ParseTable);
	for (int i = 0; i < G->numRules; i++)
	{
		int k = 0;  //iterate through all the rules
		ProductionRule rule = G->rules[i];
		Symbol left = rule.left;
		Symbol firstSymbol = rule.right[k]; 
		while (1)
		{
			if (!isTerminal(firstSymbol.name))
			{
				// for each term in first set of right symbol, insert the rule in the
				// parse table
				struct ValueFields fs = get(FirstSet, firstSymbol.name);
				int limit = fs.num;
				for (int i = 0; i < limit; i++)
				{
          if (strcmp(fs.name[i], "eps") != 0)
          {
            char *key = (char *)malloc((strlen(left.name) + strlen(fs.name[i]) + 1) * sizeof(char));
            strcpy(key, left.name);
            strcat(key, fs.name[i]);
            // printf("Entering key: %s\n", key);
            insertIntoTable(ParseTable, key, rule.right, rule.numSymbols);
          }
				}
				if (checkTerminal(FirstSet, firstSymbol.name, "eps"))  //check for epsilon in first set
				{
						if (k != rule.numSymbols - 1) //ignore till all members of the rule are done entering
						{
								firstSymbol = rule.right[++k];
								continue;
						}
						else if (k == rule.numSymbols - 1)
						{
              struct ValueFields fs = get(FollowSet, left.name); //creating follow set for case of epsilon
              int limit = fs.num;
              for (int i = 0; i < limit; i++)
              {
                  if (strcmp(fs.name[i], "eps") != 0)
                  {
                      char *key = (char *)malloc((strlen(left.name) + strlen(fs.name[i]) + 1) * sizeof(char));
                      strcpy(key, left.name);
                      strcat(key, fs.name[i]);
                      Symbol *right = (Symbol *)malloc(sizeof(Symbol));
                      strcpy(right->name, "eps");
                      insertIntoTable(ParseTable, key, right, 1); //enter null production

                      //break;//or here
                  }
                  
              }
              break;//here
						}
				}
				else
				{
						break;
				}
			}
			else
			{
				if (isTerminal(firstSymbol.name))
				{
					if (strcmp(firstSymbol.name, "eps") != 0)
					{
						char *key = (char *)malloc((strlen(left.name) + strlen(firstSymbol.name) + 1) * sizeof(char));
						strcpy(key, left.name);
						strcat(key, firstSymbol.name);
						// printf("Entering key: %s\n", key);
						insertIntoTable(ParseTable, key, rule.right, rule.numSymbols); //case of null production rule
					}
					else
					{
							struct ValueFields fs = get(FollowSet, left.name);
							int limit = fs.num;
							for (int i = 0; i < limit; i++)
							{
                if (strcmp(fs.name[i], "eps") != 0)
                {
                    char *key = (char *)malloc((strlen(left.name) + strlen(fs.name[i]) + 1) * sizeof(char));
                    strcpy(key, left.name);
                    strcat(key, fs.name[i]);
                    Symbol *right = (Symbol *)malloc(sizeof(Symbol));
                    strcpy(right->name, "eps");
                    insertIntoTable(ParseTable, key, right, 1); //entering null productions
                }
									
							}
					}
					break;
				}
			}
		}
	}
}