#ifndef __TOKEN_HKLEPSCH_H__
#define __TOKEN_HKLEPSCH_H__

#include <stdbool.h>
#include <linkedList.h>

#define RETURN_FAILURE 0
#define RETURN_SUCCESS 1


enum StringPrintingState {
    NOSTRING,
    SINGLETICK,
    DOUBLETICK,
};

enum TokenType {
    WHITESPACE,
    COMMENT,
    CLASS,
    TYPE,
    IDENTIFIER,
    FUNCTION,
    SEMICOLON,
    OPENBRACE,
    CLOSEBRACE,
    OPENPAREN,
    CLOSEPAREN,
    OPENBRACKET,
    CLOSEBRACKET,
};

struct Token {
    char * string;
    enum TokenType type;
    int bracelevel;
};


struct Token * makeToken(char * string, enum TokenType type, int bracelevel);

void freeToken(void * token);

void printToken(struct Token token);

void printTokenList(LinkedList_s * tokenList);

int tokenize(char * filename, LinkedList_s * tokenList);

char * delNReplace(char * origStr, int start, int len2Del, char * replaceStr);

char * copyString(char * origStr, int start, int len2Cpy);

bool isIdentChar(char charater);

bool isWhitespace(char character);

#endif

