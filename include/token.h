#ifndef __TOKEN_HKLEPSCH_H__
#define __TOKEN_HKLEPSCH_H__

#include <stdbool.h>
#include <linkedList.h>

#define RETURN_FAILURE 0
#define RETURN_SUCCESS 1




enum TokenType {
    WHITESPACE,
    COMMENT,
    CLASS,
    GENERAL,
    PUNCTUATION,
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
    char toBeChangedTo[50];
};

struct MangFn {
    char origName[30];
    char className[30];
    char suffix[33];
};


struct Token * makeToken(char * string, enum TokenType type, int bracelevel);

void freeToken(void * token);

struct MangFn * makeMangFn(char * origName, char * className);

void freeMangFn(void * mf);

void printToken(struct Token token);

void printTokenList(LinkedList_s * tokenList);

int tokenize(char * filename, LinkedList_s * tokenList);

int convert(char * filename, LinkedList_s * tokenList);

void getSuffix(LinkedList_s * tokens, int startInd, char * buffer);

char * delNReplace(char * origStr, int start, int len2Del, char * replaceStr);

char * copyString(char * origStr, int start, int len2Cpy);

bool isIdentChar(char charater);

bool isWhitespace(char character);

bool isClassToken(char * str);

bool strmatch(char * str1, char * str2);

enum TokenType getLastTypeExcludeWhitespace(LinkedList_s * tokenList, int i);

int indLastNotWhitespace(LinkedList_s * tokenList, int i);

bool isNumber(char c);

bool isSpecial(char c);



#endif

