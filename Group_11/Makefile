
#Group 11
#Rudra Jewalikar (2021A7PS0450P)
#Dhruv Shrimali (2021A7PS0008P)
#Salil Godbole (2021A7PS2004P)
#Shyam Raghavan (2021A7PS0013P)
#Sarthak Sharma (2021A7PS2535P)

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# List of source files
SRCS = TD.c parserDef.c grammarParser.c lexer.c parseTable.c parser.c parseTree.c stack.c lexerDef.c driver.c

# List of object files (generated from source files)
OBJS = $(SRCS:.c=.o)

# Header files
HDRS = TD.h parserDef.h grammarParser.h lexer.h parseTable.h parser.h parseTree.h stack.h lexerDef.h

# The main target, linking all object files to form the executable
stage1exe: $(OBJS)
		$(CC) $(CFLAGS) -o stage1exe $(OBJS)

# Compile each source file into its object file
%.o: %.c $(HDRS)
		$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
		rm -f stage1exe $(OBJS)
