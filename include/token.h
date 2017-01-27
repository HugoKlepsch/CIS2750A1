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

struct String {
    char str[100];
};

struct Variable {
    char type[30];
    char name[30];
    char value[200];
};

struct MangFn {
    char returnType[40];
    char origName[30];
    char paramString[200];
    char className[30];
    char suffix[33];
    struct Variable localVars[100];
    int numLocalVars;
};


struct Class {
    char className[30];
    struct MangFn * memberFns[100];
    int numMemFn;
    struct Variable memberVars[300];
    int numMemVar;
};

struct Global {
    struct Class classes[50];
    int numClasses;
    struct Variable globalVars[100];
    int numVars;
};


void makeClass(struct Class * obj, char * className);


struct Token * makeToken(char * string, enum TokenType type, int bracelevel);

void freeToken(void * token);


void makeMangFn(struct MangFn * obj, char * origName, char * className);


void printToken(struct Token token);

void printTokenList(LinkedList_s * tokenList);

void printTokenListFile(LinkedList_s * tokenList, char * filename);


int tokenize(char * filename, LinkedList_s * tokenList);

int convert(char * filename, LinkedList_s * tokenList);


void analyzeFn(struct MangFn * obj, LinkedList_s * tokens, int startInd, char * className);

void analyzeClass(struct Class * obj, LinkedList_s * tokens, int startInd);


void getSuffix(LinkedList_s * tokens, int startInd, char * buffer, char * wholeString);


void insertThis(LinkedList_s * tokens, int startInd, char * className);

bool isVariable(LinkedList_s * tokens, int startInd);

bool isFunction(LinkedList_s * tokens, int startInd);


char * delNReplace(char * origStr, int start, int len2Del, char * replaceStr);

char * copyString(char * origStr, int start, int len2Cpy);

void ll2String(LinkedList_s * tokens, int start, int end, char * buffer);

bool isIdentChar(char charater);

bool isWhitespace(char character);

bool isClassToken(char * str);

bool strmatch(char * str1, char * str2);

bool isNumber(char c);

bool isSpecial(char c);


enum TokenType getLastTypeExcludeWhitespace(LinkedList_s * tokenList, int i);

int indLastNotWhitespace(LinkedList_s * tokenList, int i);

int indNextType(LinkedList_s * tokens, int startInd, enum TokenType type);

int indPrevType(LinkedList_s * tokens, int startInd, enum TokenType type);

int indEndLast(LinkedList_s * tokens, int startInd);

enum TokenType getType(LinkedList_s * tokens, int ind);



#endif
