/*
Group 11
Rudra Jewalikar (2021A7PS0450P)
Dhruv Shrimali (2021A7PS0008P)
Salil Godbole (2021A7PS2004P)
Shyam Raghavan (2021A7PS0013P)
Sarthak Sharma (2021A7PS2535P)
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexerDef.h"
#define BUFFER_SIZE 200

struct TokenInfo {
		char* token;
		char lexeme[22];
		int lineNo;
		int IntValue;
		float FloatValue;
};

// Function to handle powers
float Power(double base, int exponent) {
  double result = 1.0;
  for (int i = 0; i < exponent; ++i) {
    result *= base;
  }
  return result;
}

// Function to convert string to int
int convertStringToInt(const char *str) {
  char *endptr;
  int intVal;

  // convert to integer
  intVal = strtol(str, &endptr, 10);
  if (*endptr == '\0') {
    // printf("%d\n", intVal);
    return intVal;
  }
  return 0;
}

// Function to convert string to float
float convertStringToFloat(const char *str) {
  char *endptr;
  float floatVal;

  floatVal = strtof(str, &endptr);
  if (*endptr == '\0') {
    // printf("%.2f\n", floatVal);
    return floatVal;
  }

  // convert exponent
  char *p = strchr(str, 'E');
  if (p != NULL) {
    int base = atoi(str);
    int exp = atoi(p + 1);
    double result = Power(base, exp);
    // printf("%.2lf\n", result);
    return result;
  }
  return 0.0;
}

struct TokenInfo getNextToken(char *buffer, int *i, int *j, int *line_number,
                              struct HashTableST *ht) {
  int state = 1;
  if (buffer[*j] == '\0') {
    state = -1;
  } else if (buffer[*j] == '+')
    state = 1;
  else if (buffer[*j] == '-')
    state = 2;
  else if (buffer[*j] == '*')
    state = 3;
  else if (buffer[*j] == '/')
    state = 4;
  else if (buffer[*j] == '(')
    state = 5;
  else if (buffer[*j] == '[')
    state = 6;
  else if (buffer[*j] == ';')
    state = 7;
  else if (buffer[*j] == ')')
    state = 8;
  else if (buffer[*j] == ']')
    state = 9;
  else if (buffer[*j] == ':')
    state = 10;
  else if (buffer[*j] == '~')
    state = 11;
  else if (buffer[*j] == ',')
    state = 12;
  else if (buffer[*j] == '&')
    state = 13;
  else if (buffer[*j] == '.')
    state = 16;
  else if (buffer[*j] == '@')
    state = 17;
  else if (buffer[*j] == '#')
    state = 20;
  else if (buffer[*j] == '_')
    state = 23;
  else if (buffer[*j] == '<')
    state = 28;
  else if (buffer[*j] == '>')
    state = 35;
  else if (buffer[*j] == '=')
    state = 38;
  else if (buffer[*j] == '!')
    state = 40;
  else if (buffer[*j] == 'a' || (buffer[*j] >= 'A' && buffer[*j] <= 'Z') ||
           (buffer[*j] >= 'e' && buffer[*j] <= 'z'))
    state = 42;
  else if (buffer[*j] >= 'b' && buffer[*j] <= 'd')
    state = 44;
  else if (buffer[*j] >= '0' && buffer[*j] <= '9')
    state = 52;
  else if (buffer[*j] == ' ' || buffer[*j] == '\t' || buffer[*j] == '\n')
    state = 63;
  else if (buffer[*j] == '$') {// end character for parser
    if (buffer[((*j) + 1) % BUFFER_SIZE] == '\0') { // if end character comes at end then return special $, else unknown symbol
      struct TokenInfo result;
      result.token = "$";
      result.lexeme[0] = '$';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    } else {
      struct TokenInfo result;
      result.token = "UNKNOWN";
      result.lexeme[0] = '$';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    }
  } else {
    struct TokenInfo result;
    result.token = "UNKNOWN";
    result.lexeme[0] = buffer[*j];
    result.lexeme[1] = '\0';
    result.lineNo = *line_number;
    return result;
  }
  while (state != -1) {
    switch (state) {
      struct TokenInfo result;
      int lexemeLength;
      int itr;
    case 1:
      result.token = "TK_PLUS";
      result.lexeme[0] = '+';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 2:
      result.token = "TK_MINUS";
      result.lexeme[0] = '-';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 3:
      result.token = "TK_MUL";
      result.lexeme[0] = '*';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 4:
      result.token = "TK_DIV";
      result.lexeme[0] = '/';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 5:
      result.token = "TK_OP";
      result.lexeme[0] = '(';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 6:
      result.token = "TK_SQL";
      result.lexeme[0] = '[';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 7:
      result.token = "TK_SEM";
      result.lexeme[0] = ';';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 8:
      result.token = "TK_CL";
      result.lexeme[0] = ')';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 9:
      result.token = "TK_SQR";
      result.lexeme[0] = ']';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 10:
      result.token = "TK_COLON";
      result.lexeme[0] = ':';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 11:
      result.token = "TK_NOT";
      result.lexeme[0] = '~';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 12:
      result.token = "TK_COMMA";
      result.lexeme[0] = ',';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 13:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '&') {
        state = 14;
        continue;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 14:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '&') {
        state = 15;
        continue;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 15:
      result.token = "TK_AND";
      result.lexeme[0] = '&';
      result.lexeme[1] = '&';
      result.lexeme[2] = '&';
      result.lexeme[3] = '\0';
      result.lineNo = *line_number;
      return result;
    case 16:
      result.token = "TK_DOT";
      result.lexeme[0] = '.';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 17:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '@') {
        state = 18;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 18:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '@') {
        state = 19;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 19:
      result.token = "TK_OR";
      result.lexeme[0] = '@';
      result.lexeme[1] = '@';
      result.lexeme[2] = '@';
      result.lexeme[3] = '\0';
      result.lineNo = *line_number;
      return result;
    case 20:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] >= 'a' && buffer[*i] <= 'z') {
        state = 21;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 21:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      while (buffer[*i] >= 'a' && buffer[*i] <= 'z') {
        (*i)++;
        (*i) = (*i) % BUFFER_SIZE;
      }
    case 22:
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j) +1;
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i) +1;
      }
      if (lexemeLength > 21) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        result.lineNo = *line_number;
        return result;
      }
      itr = 0;
      for (int k = *j; k != (*i)+1; k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      result.token = "TK_RUID";
      result.lineNo = *line_number;
      return result;
    case 23:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if ((buffer[*i] >= 'a' && buffer[*i] <= 'z') ||
          (buffer[*i] >= 'A' && buffer[*i] <= 'Z')) {
        state = 24;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 24:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      while ((buffer[*i] >= 'a' && buffer[*i] <= 'z') || (buffer[*i] >= 'A' && buffer[*i] <= 'Z')) {
        (*i)++;
        (*i) = (*i) % BUFFER_SIZE;
      }
      if (buffer[*i] >= '0' && buffer[*i] <= '9') {
        state = 25;
      } else {
        state = 26;
        continue;
      }
    case 25:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      while (buffer[*i] >= '0' && buffer[*i] <= '9') {
        (*i)++;
        (*i) = (*i) % BUFFER_SIZE;
      }
      state = 27;
    case 27: // case 27 first instead of 26 due to fall through
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j);
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i);
      }
      if (lexemeLength > 21) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
      itr = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_FUNID";
      result.lineNo = *line_number;
      return result;
    case 26: { // case of _main
      int subarray_length;
      if ((*j) <= (*i)) {
        subarray_length = (*i) - (*j);
      } else {
        subarray_length = BUFFER_SIZE - (*j) + (*i);
      }
      if (subarray_length > 21) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
      char string[subarray_length + 1];
      int l = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        string[l] = buffer[k];
        l++;
      }
      string[l] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      struct TokenFieldsST retrieved_fields = getST(ht, strdup(string));
      strncpy(result.lexeme, string, subarray_length + 1);
      if (retrieved_fields.token == NULL && retrieved_fields.line_no == 0) {
        struct TokenFieldsST fields;
        fields.token = "TK_FUNID";
        fields.line_no = *line_number;
        insertST(ht, string, fields);
        result.token = "TK_FUNID";
        result.lineNo = *line_number;
        return result;
      } else {
        result.token = retrieved_fields.token;
        result.lineNo = *line_number;
        return result;
      }
    }
    case 28:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '=') {
        state = 29;
      } else if (buffer[*i] == '-') {
        state = 30;
        continue;
      } else {
        state = 34;
        continue;
      }
    case 29:
      result.token = "TK_LE";
      result.lexeme[0] = '<';
      result.lexeme[1] = '=';
      result.lexeme[2] = '\0';
      result.lineNo = *line_number;
      return result;
    case 30:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '-') {
        state = 31;
      } else {
        state = 33;
        continue;
      }
    case 31:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '-') {
        state = 32;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 32:
      result.token = "TK_ASSIGNOP";
      result.lexeme[0] = '<';
      result.lexeme[1] = '-';
      result.lexeme[2] = '-';
      result.lexeme[3] = '-';
      result.lexeme[4] = '\0';
      result.lineNo = *line_number;
      return result;
    case 33:
      (*i) = (*i) + BUFFER_SIZE - 2;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_LT";
      result.lexeme[0] = '<';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 34:
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_LT";
      result.lexeme[0] = '<';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 35:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '=') {
        state = 36;
      } else {
        state = 37;
        continue;
      }
    case 36:
      result.token = "TK_GE";
      result.lexeme[0] = '>';
      result.lexeme[1] = '=';
      result.lexeme[2] = '\0';
      result.lineNo = *line_number;
      return result;
    case 37:
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_GT";
      result.lexeme[0] = '>';
      result.lexeme[1] = '\0';
      result.lineNo = *line_number;
      return result;
    case 38:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '=') {
        state = 39;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 39:
      result.token = "TK_EQ";
      result.lexeme[0] = '=';
      result.lexeme[1] = '=';
      result.lexeme[2] = '\0';
      result.lineNo = *line_number;
      return result;
    case 40:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '=') {
        state = 41;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 41:
      result.token = "TK_NE";
      result.lexeme[0] = '!';
      result.lexeme[1] = '=';
      result.lexeme[2] = '\0';
      result.lineNo = *line_number;
      return result;
    case 42:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      while (buffer[*i] >= 'a' && buffer[*i] <= 'z') {
        (*i)++;
        (*i) = (*i) % BUFFER_SIZE;
      }
      state = 43;
    case 43: {
      int subarray_length;
      if ((*j) <= (*i)) {
        subarray_length = (*i) - (*j) + 1;
      } else {
        subarray_length = BUFFER_SIZE - (*j) + (*i) + 1;
      }
      if (subarray_length > 20) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
      char string[subarray_length];
      int l = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        string[l] = buffer[k];
        l++;
      }
      string[subarray_length - 1] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      strncpy(result.lexeme, string, subarray_length);
      struct TokenFieldsST retrieved_fields = getST(ht, strdup(string));
      if (retrieved_fields.token == NULL && retrieved_fields.line_no == 0) {
        struct TokenFieldsST fields;
        fields.token = "TK_FIELDID";
        fields.line_no = *line_number;
        insertST(ht, string, fields);
        result.token = "TK_FIELDID";
        result.lineNo = *line_number;
        return result;
        result.lineNo = *line_number;
      } else {
        result.token = retrieved_fields.token;
        result.lineNo = *line_number;
        return result;
      }
    }
    case 44:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] >= 'a' && buffer[*i] <= 'z') {
        state = 42;
        continue;
      } else if (buffer[*i] >= '0' && buffer[*i] <= '9') {
        state = 45;
      } else {
        state = 49;
        continue;
      }
    case 45:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] >= 'b' && buffer[*i] <= 'd') {
        state = 46;
      } else if (buffer[*i] >= '2' && buffer[*i] <= '7') {
        state = 47;
        continue;
      } else {
        state = 50;
        continue;
      }
    case 46:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      while (buffer[*i] >= 'b' && buffer[*i] <= 'd') {
        (*i)++;
        (*i) = (*i) % BUFFER_SIZE;
      }
      if (buffer[*i] >= '2' && buffer[*i] <= '7') {
        state = 47;
      } else {
        state = 51;
        continue;
      }
    case 47:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      while (buffer[*i] >= '2' && buffer[*i] <= '7') {
        (*i)++;
        (*i) = (*i) % BUFFER_SIZE;
      }
      state = 48;
    case 48:
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j);
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i);
      }
      if (lexemeLength > 20) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
      itr = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_ID";
      result.lineNo = *line_number;
      return result;
    case 49:
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j);
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i);
      }
      itr = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_FIELDID";
      result.lineNo = *line_number;
      return result;
    case 50:
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j);
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i);
      }
      itr = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_ID";
      result.lineNo = *line_number;
      return result;
    case 51:
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j);
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i);
      }
      if (lexemeLength > 20) {
        result.token = "LONG_ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lexeme[0] = '\0';
        result.lineNo = *line_number;
        return result;
      }
      itr = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_ID";
      result.lineNo = *line_number;
      return result;
    case 52:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      while (buffer[*i] >= '0' && buffer[*i] <= '9') {
        (*i)++;
        (*i) = (*i) % BUFFER_SIZE;
      }
      if (buffer[*i] == '.') {
        state = 53;
      } else {
        state = 60;
        continue;
      }
    case 53:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] >= '0' && buffer[*i] <= '9') {
        state = 54;
      } else {
        state = 61;
        continue;
      }
    case 54:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] >= '0' && buffer[*i] <= '9') {
        state = 55;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 55:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == 'E') {
        state = 56;
      } else {
        state = 62;
        continue;
      }
    case 56:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] == '+' || buffer[*i] == '-') {
        state = 57;
      } else if (buffer[*i] >= '0' && buffer[*i] <= '9') {
        state = 58;
        continue;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 57:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if (buffer[*i] >= '0' && buffer[*i] <= '9') {
        state = 58;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 58:
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      if ((buffer[*i] >= '0') && (buffer[*i] <= '9')) {
        state = 59;
      } else {
        if ((*j) <= (*i)) {
          lexemeLength = (*i) - (*j);
        } else {
          lexemeLength = BUFFER_SIZE - (*j) + (*i);
        }
        itr = 0;
        for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
          result.lexeme[itr++] = buffer[k];
        }
        result.lexeme[itr] = '\0';
        result.token = "ERROR";
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
    case 59:
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j) + 1;
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i) + 1;
      }
      if (lexemeLength > 20) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        result.lineNo = *line_number;
        return result;
      }
      itr = 0;
      for (int k = *j; k != (*i + 1); k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      result.token = "TK_RNUM";
      result.lineNo = *line_number;
      result.FloatValue = convertStringToFloat(result.lexeme);
      return result;
    case 60:
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j);
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i);
      }
      if (lexemeLength > 20) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
      itr = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_NUM";
      result.lineNo = *line_number;
      result.IntValue = convertStringToInt(result.lexeme);
      return result;
    case 61:
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j) - 1;
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i) - 1;
      }
      if (lexemeLength > 20) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        (*i) = (*i) + BUFFER_SIZE - 2;
        result.lineNo = *line_number;
        return result;
      }
      itr = 0;
      for (int k = *j; k != (*i) - 1; k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 2;
      // *j-1 because of double retraction
      result.token = "TK_NUM";
      result.lineNo = *line_number;
      result.IntValue = convertStringToInt(result.lexeme);
      return result;
    case 62:
      if ((*j) <= (*i)) {
        lexemeLength = (*i) - (*j);
      } else {
        lexemeLength = BUFFER_SIZE - (*j) + (*i);
      }
      if (lexemeLength > 20) {
        result.token = "LONG_ERROR";
        result.lexeme[0] = '\0';
        (*i) = (*i) + BUFFER_SIZE - 1;
        (*i) = (*i) % BUFFER_SIZE;
        result.lineNo = *line_number;
        return result;
      }
      itr = 0;
      for (int k = *j; k != (*i); k = (k + 1) % BUFFER_SIZE) {
        result.lexeme[itr++] = buffer[k];
      }
      result.lexeme[itr] = '\0';
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "TK_RNUM";
      result.lineNo = *line_number;
      result.FloatValue = convertStringToFloat(result.lexeme);
      return result;
    case 63:
      if (buffer[*i] == '\n') {
        (*line_number)++;
      }
      (*i)++;
      (*i) = (*i) % BUFFER_SIZE;
      while (buffer[*i] == ' ' || buffer[*i] == '\t' || buffer[*i] == '\n') {
        if (buffer[*i] == '\n') {
          (*line_number)++;
        }
        (*i)++;
        (*i) = (*i) % BUFFER_SIZE;
      }
      state = 64;
    case 64:
      (*i) = (*i) + BUFFER_SIZE - 1;
      (*i) = (*i) % BUFFER_SIZE;
      result.token = "NOTHING";
      result.lexeme[0] = '\0';
      result.lineNo = *line_number;
      return result;
    default:
      result.token = "ERROR";
      result.lexeme[0] = '\0';
      result.lineNo = *line_number;
      return result;
    }
  }
}