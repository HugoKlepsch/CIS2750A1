#ifndef __TOKEN_HKLEPSCH_H__
#define __TOKEN_HKLEPSCH_H__

#include <stdbool.h>
#include <linkedList.h>

#define RETURN_FAILURE 0
#define RETURN_SUCCESS 1

enum lastPrintedType {
    WHITESPACE,
    CHARACTER,
    PUNCTUATION,
    NONE
};

enum StringPrintingState {
    NOSTRING,
    SINGLETICK,
    DOUBLETICK,
};

enum TokenType {
    COMMENT,
    IDENTIFIER,
    FUNCTION,
    DELIMITEROPEN,
    DELIMITERCLOSE,
    LINEEND,
    CLASS,
    TYPE,
};

struct Token {
    char * string;
    enum TokenType type;
};

struct Token * makeToken(char * string, enum TokenType type);

void freeToken(void * token);

int tokenize(char * filename, LinkedList_s * tokenList);

char * delNReplace(char * origStr, int start, int len2Del, char * replaceStr);

bool isIdentChar(char charater);

#endif

