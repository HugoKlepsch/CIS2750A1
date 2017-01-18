#ifndef __TOKEN_HKLEPSCH_H__
#define __TOKEN_HKLEPSCH_H__

#include <stdbool.h>
#include <linkedList.h>

#define RETURN_FAILURE 0
#define RETURN_SUCCESS 1



enum ScopeType {
    GLOBAL, 
    LOCAL,
    CLASS,
}

enum TokenType {
    WHITESPACE,
    COMMENT,
    CLASS,
    TYPE,
    CLASSNAME,
    VARNAME,
    FUNCTIONNAME,
    PARAMETER,
    GENERAL,
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

bool isClassToken(char * str);

bool strmatch(char * str1, char * str2);

enum TokenType getLastTypeExcludeWhitespace(LinkedList_s * tokenList);

#endif

