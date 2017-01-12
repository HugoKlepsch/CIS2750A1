#ifndef __TOKEN_HKLEPSCH_H__
#define __TOKEN_HKLEPSCH_H__

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

int tokenize(char * filename);

#endif

