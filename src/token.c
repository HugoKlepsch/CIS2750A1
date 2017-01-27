#include <token.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <linkedList.h>

void test_copyString() {
    char exStr[] = "example string";
    char * newStr = copyString(exStr, 0, 7);
    printf("%s\n", newStr);
    free(newStr);

    newStr = copyString(exStr, 2, 3);
    printf("%s\n", newStr);
    free(newStr);

    newStr = copyString(exStr, 10, 10);
    printf("%s\n", newStr);
    free(newStr);

}


void test() {
    int length;
    /*char exStr[] = "This is an example string."; */
    /*char exStr[] = "This"; */
    char exStr[] = "\tclass A {";
    length = strlen(exStr) + 1;
    char * newStr = malloc(length);
    strcpy(newStr, exStr);
    printf("%s\n", newStr);

    strcpy(newStr, exStr);
    newStr = delNReplace(newStr, 1, 5, "struct");
    printf("%s\n", newStr);
    free(newStr);

    test_copyString();

    LinkedList_s head;
    initList_s(&head);
    struct Token * temp;

    temp = makeToken("this", GENERAL, 0);
    addNodeEnd_s(&head, temp);

    temp = makeToken("is", GENERAL, 1);
    addNodeEnd_s(&head, temp);

    temp = makeToken("a", GENERAL, 2);
    addNodeEnd_s(&head, temp);

    temp = makeToken("test", GENERAL, 3);
    addNodeEnd_s(&head, temp);

    temp = makeToken("of", GENERAL, 4);
    addNodeEnd_s(&head, temp);

    temp = makeToken("reorder", GENERAL, 5);
    addNodeEnd_s(&head, temp);



    printTokenList(&head);
    cutPasteInsertAfter(&head, 3, 3, 1);
    puts("");
    printTokenList(&head);

    destroyList_s(&head, NULL);
}


int main(int argc, char ** argv) {
    char filename[100];
    char outfilename[100] = "out.c";

    /* needs one arg of the filename */
    if (argc != 2) {
        printf("needs to be run with filename!\n");
        test();
        return EXIT_FAILURE;
    }

    strncpy(filename, argv[1], 100);
    /* assuring that the filename is null-terminated */
    filename[99] = '\0';

    LinkedList_s tokens;
    if (initList_s(&tokens) == 0) {
        /*failed to initialize the list */
        printf("Failed to initialize storage structure\n");
        return EXIT_FAILURE;
    }

    /* lets tokenize the file */
    if (tokenize(filename, &tokens) == RETURN_FAILURE) {
        /*failed to tokenize file*/
        printf("Failed to tokenize file\n");
        destroyList_s(&tokens, &freeToken);
        return EXIT_FAILURE;
    }

    if (convert(outfilename, &tokens) == RETURN_FAILURE) {
        /*failed to convert file*/
        printf("Failed to convert file\n");
        destroyList_s(&tokens, &freeToken);
        return EXIT_FAILURE;
    }

    printTokenListFile(&tokens, "output.txt");

    destroyList_s(&tokens, &freeToken);
    return EXIT_SUCCESS;
}


void makeClass(struct Class * obj, char * className) {
    struct Class * class = obj;
    strcpy(class->className, className);
    class->numMemFn = 0;
    class->numMemVar = 0;

    int i;
    for (i = 0; i < 300; ++i) {
        int j;
        for (j = 0; j < 30; ++j) {
            /* zero the strings in memberVars */
            class->memberVars[i].type[j] = '\0';
            class->memberVars[i].name[j] = '\0';
        }
    }
}


struct Token * makeToken(char * string, enum TokenType type, int bracelevel) {
    struct Token * newToken;
    newToken = malloc(sizeof(*newToken));
    newToken->string = string;
    newToken->type = type;
    newToken->bracelevel = bracelevel;
    return newToken;
}


void freeToken(void * token) {
    struct Token * givenToken = (struct Token *) token;
    free(givenToken->string);
    free(givenToken);
}


void makeMangFn(struct MangFn * obj, char * origName, char * className) {
    struct MangFn * newMF = obj;
    strcpy(newMF->origName, origName);
    strcpy(newMF->className, className);
    int i;
    for (i = 0; i < 32; ++i) {
        newMF->suffix[i] = '\0';
    }
    for (i = 0; i < 200; ++i) {
        newMF->paramString[i] = '\0';
    }
    newMF->numLocalVars = 0;
}


void printToken(struct Token token) {
    printf("\"%s\"::%d::", token.string, token.bracelevel);
    switch (token.type) {
        case WHITESPACE:
            printf("WHITESPACE\n");
            break;
        case COMMENT:
            printf("COMMENT\n");
            break;
        case CLASS:
            printf("CLASS\n");
            break;
        case GENERAL:
            printf("GENERAL\n");
            break;
        case PUNCTUATION:
            printf("PUNCTUATION\n");
            break;
        case SEMICOLON:
            printf("SEMICOLON\n");
            break;
        case OPENBRACE:
            printf("OPENBRACE\n");
            break;
        case CLOSEBRACE:
            printf("CLOSEBRACE\n");
            break;
        case OPENPAREN:
            printf("OPENPAREN\n");
            break;
        case CLOSEPAREN:
            printf("CLOSEPAREN\n");
            break;
        case OPENBRACKET:
            printf("OPENBRACKET\n");
            break;
        case CLOSEBRACKET:
            printf("CLOSEBRACKET\n");
            break;
    }
}


void printTokenList(LinkedList_s * tokenList) {
    int i;
    struct Token * tempToken;
    for (i = 0; i < length_s(tokenList); ++i) {
        tempToken = (struct Token *) getData_s(tokenList, i);
        printf("%d", i);
        printToken(*tempToken);
    }
}


void printTokenListFile(LinkedList_s * tokenList, char * filename) {
    FILE * fp = fopen(filename, "w");
    if (!fp) {
        puts("could not open file for writing!");
        return;
    }

    int i;
    struct Token * tempToken;
    for (i = 0; i < length_s(tokenList); ++i) {
        tempToken = (struct Token *) getData_s(tokenList, i);
        fprintf(fp, "%s", tempToken->string);
    }
    fclose(fp);

}


int tokenize(char * filename, LinkedList_s * tokenList) {
    char buffer[512];
    char * wholeFile = malloc(512);
    if (!wholeFile) {
        puts("Failed to get memory");
        return RETURN_FAILURE;
    }
    wholeFile[0] = '\0';

    FILE * inFP = fopen(filename, "r");
    if (inFP == NULL) {
        printf("Failed to open given file!\n");
        free(wholeFile);
        return RETURN_FAILURE;
    }

    /* read every line of the file */
    while(fgets(buffer, 512, inFP)) {
        wholeFile = realloc(wholeFile, strlen(wholeFile) + strlen(buffer) + 1);
        strcat(wholeFile, buffer);
    }
    fclose(inFP);
    printf("%s", wholeFile);




    /*tokenize file*/
    int i = 0;
    int traverseInd = 0;
    int bracelevel = 0;
    while (wholeFile[i] != '\0') {
        char * tokenBuffer;
        struct Token * tempToken;
        if (isWhitespace(wholeFile[i])) {
            /*tokenize whitespace together */
            for (traverseInd = i;
                    wholeFile[traverseInd] != '\0'
                    && isWhitespace(wholeFile[traverseInd]);
                    ++traverseInd) {
                /*continue while there's whitespace */
            }
            tokenBuffer = copyString(wholeFile, i, (traverseInd - i));
            tempToken = makeToken(tokenBuffer, WHITESPACE, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '/' && wholeFile[i+1] == '/') {
            /*tokenize single line comments together*/
            for (traverseInd = i;
                    wholeFile[traverseInd] != '\0'
                    && wholeFile[traverseInd] != '\n';
                    ++traverseInd) {
                /*continue on the same line*/
            }
            tokenBuffer = copyString(wholeFile, i, (traverseInd - i));
            tempToken = makeToken(tokenBuffer, COMMENT, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '/' && wholeFile[i+1] == '*') {
            /*tokenize multi line comments together*/
            for (traverseInd = i;
                    wholeFile[traverseInd] != '\0'
                    && !(wholeFile[traverseInd] == '*' && wholeFile[traverseInd] == '/');
                    ++traverseInd) {
                /*continue until multi-line end characters reached*/
            }
            tokenBuffer = copyString(wholeFile, i, (traverseInd - i));
            tempToken = makeToken(tokenBuffer, COMMENT, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '-') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '+') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '*') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '/') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '=') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '&') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '<') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '>') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == ',') {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '.' &&
                !isNumber(wholeFile[i-1]) &&
                !isNumber(wholeFile[i+1])) {
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, PUNCTUATION, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (isClassToken(&wholeFile[i])){
            /* match 'class' token */
            for (traverseInd = i;
                    wholeFile[traverseInd] != '\0'
                    && isIdentChar(wholeFile[traverseInd]);
                    ++traverseInd) {
                /*continue until not a valid identifyer char*/
            }
            tokenBuffer = copyString(wholeFile, i, (traverseInd - i));
            tempToken = makeToken(tokenBuffer, CLASS, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '"') {
            /*find whole string */
            for (traverseInd = i + 1;
                    wholeFile[traverseInd] != '\0'
                    && !(wholeFile[traverseInd] == '"' && wholeFile[traverseInd-1] != '\\');
                    ++traverseInd) {
                /*continue until not a valid identifyer char*/
            }
            traverseInd++;
            tokenBuffer = copyString(wholeFile, i, (traverseInd - i));
            tempToken = makeToken(tokenBuffer, GENERAL, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == ';') {
            /* consume a single semicolon */
            traverseInd = i + 1;
            tokenBuffer = copyString(wholeFile, i, (traverseInd - i));
            tempToken = makeToken(tokenBuffer, SEMICOLON, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        }  else if (wholeFile[i] == '(') {
            /* open parenthesis */
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, OPENPAREN, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == ')') {
            /* open parenthesis */
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, CLOSEPAREN, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '{') {
            /* open brace */
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, OPENBRACE, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
            ++bracelevel;
        } else if (wholeFile[i] == '}') {
            /* close brace */
            --bracelevel;
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, CLOSEBRACE, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == '[') {
            /* open brace */
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, OPENBRACKET, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else if (wholeFile[i] == ']') {
            /* close brace */
            tokenBuffer = copyString(wholeFile, i, 1);
            tempToken = makeToken(tokenBuffer, OPENBRACKET, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        } else {
            /* anything else keking for real */
            for (traverseInd = i + 1;
                    wholeFile[traverseInd] != '\0' &&
                    !isWhitespace(wholeFile[traverseInd]) &&
                    !isSpecial(wholeFile[traverseInd]);
                    ++traverseInd) {
                /*continue until not a valid identifyer char*/
            }
            tokenBuffer = copyString(wholeFile, i, (traverseInd - i));
            tempToken = makeToken(tokenBuffer, GENERAL, bracelevel);
            addNodeEnd_s(tokenList, tempToken);
        }



        /*must be at the end of the while loop to ensure that the loop
         * continues to look at new characters */
        if (i >= traverseInd) {++i;} else { i = traverseInd;}
    }

    printTokenList(tokenList);
    free(wholeFile);


    return RETURN_SUCCESS;

}


int convert(char * filename, LinkedList_s * tokenList) {


    printTokenList(tokenList);


    return RETURN_SUCCESS;
}


void analyzeFn(struct MangFn * obj, LinkedList_s * tokens, int startInd, char * className) {
    int i = startInd;

    int indOpenParen = indNextType(tokens, i, OPENPAREN);
    int indCloseParen = indNextType(tokens, indOpenParen, CLOSEPAREN);

    int indName = indLastNotWhitespace(tokens, indOpenParen);

    int startOfType = indEndLast(tokens, indName) + 1; /* +1 to not include the last statement */
    if (getType(tokens, startOfType) == WHITESPACE) {
        startOfType += 1; /* also skip whitespace */
    }

    ll2String(tokens, startOfType, indName - 1, obj->returnType);
    strcpy(obj->className, className);
    strcpy(obj->origName, ((struct Token *)getData_s(tokens, indName))->string);
    getSuffix(tokens, indOpenParen, obj->suffix, obj->paramString);

    /* now get local variables */

}


void analyzeClass(struct Class * obj, LinkedList_s * tokens, int startInd) {
    struct Class * class = obj;
    struct Token * tok;
    int i;

    /* traverse to the start of the class */
    i = indNextType(tokens, startInd, OPENBRACE);

    /* get all member variables
    there will be only variables before only functions */
    for (; i < length_s(tokens); ++i) {
        tok = getData_s(tokens, i);
        if (tok->type == CLOSEBRACE && tok->bracelevel == 0) {
            /* end of class */
            break;
        }

        if (tok->type == WHITESPACE) {continue;}

        if (isVariable(tokens, i)) {
            char type[30];
            strcpy(type, tok->string);

            char varName[30];
            struct Token * t = getData_s(tokens, i+2); /*traverse to varname */
            strcpy(varName, t->string);

            int indSemicolon, indEquals;
            indSemicolon = indNextType(tokens, i, SEMICOLON);

            bool keepGoing = true;
            indEquals = i;
            while (keepGoing) {
                indEquals = indNextType(tokens, indEquals, PUNCTUATION);
                struct Token * tempTok = getData_s(tokens, indEquals);
                if (tempTok->string[0] == '=' || indEquals == -1) {
                    keepGoing = false;
                }
            }
            char value[200];
            value[0] = '\0';
            if (indEquals < indSemicolon) {
                /* variable is defined as well as declared */
                ll2String(tokens, indEquals, indSemicolon, value);
            }
            strcpy(obj->memberVars[numMemVar].type, type);
            strcpy(obj->memberVars[numMemVar].name, varName);
            strcpy(obj->memberVars[numMemVar++].value, value);
            i = indSemicolon;
        } else {
            break; /* no longer in variables */
        }
    }

    /* traverse to the start of the class */
    i = indNextType(tokens, startInd, OPENBRACE);
    /* get all member functions */
    for (; i < length_s(tokens); ++i) {
        tok = getData_s(tokens, i);
        if (tok->type == CLOSEBRACE && tok->bracelevel == 0) {
            /* end of class */
            break;
        }

        if (tok->type == WHITESPACE) {continue;}

        if (isFunction(tokens, i)) {
            analyzeFn(obj->memberFns[numMemFn++], tokens, i, obj->className);
        } else {
        }
    }
}


void getSuffix(LinkedList_s * tokens, int startInd, char * buffer, char * paramString) {
    int i = startInd;
    int count = 0;
    bool keepGoing = true;
    for (i = startInd; i < length_s(tokens) && keepGoing; ++i) {
        struct Token * tok = getData_s(tokens, i);
        if (tok->type == CLOSEPAREN) {
            break;
        }
        if (tok->type == OPENPAREN) {
            continue;
        }
        if (tok->type != GENERAL) {
            continue;
        }

        /* todo grab one, traverse to punc */
        buffer[count++] = tok->string[0];
        int j;
        for (j = i; j < length_s(tokens); ++j) {
            tok = getData_s(tokens, j);
            if (tok->type == PUNCTUATION &&
                    tok->string[0] == ',') {
                /* traverse to the next parameter */
                break;
            } else if (tok->type == CLOSEPAREN) {
                keepGoing = false;
            }
        }
        i = j;
    }

    bool recording = false;
    for (i = startInd; i < length_s(tokens) && keepGoing; ++i) {
        struct Token * tok = getData_s(tokens, i);
        if (tok->type == OPENPAREN) {
            recording = true;
            continue;
        }
        if (tok->type == CLOSEPAREN) {
            keepGoing = false;
            break;
        }
        if (recording) {
            strcat(paramString, tok->string);
        }
    }
}

void insertThis(LinkedList_s * tokens, int startInd, char * className) {
    int i = startInd;
    bool keepGoing = true;
    for (i = startInd; i < length_s(tokens) && keepGoing; ++i) {
        struct Token * tok = getData_s(tokens, i);
        if (tok->type == CLOSEPAREN) {
            break;
        }
        if (tok->type != OPENPAREN) {
            continue;
        }
        /* we are now at a OPENPAREN */

        /* add the type info */
        char * tempStr = malloc(40);
        sprintf(tempStr, "struct %s *", className);
        tok = makeToken(tempStr, GENERAL, 1);
        addNodeInsert_s(tokens, tok, i + 1);

        /* add whitespace */
        tempStr = malloc(40);
        sprintf(tempStr, " ");
        tok = makeToken(tempStr, WHITESPACE, 1);
        addNodeInsert_s(tokens, tok, i + 2);

        /* add variablename */
        tempStr = malloc(40);
        sprintf(tempStr, "this");
        tok = makeToken(tempStr, GENERAL, 1);
        addNodeInsert_s(tokens, tok, i + 3);

        break;
    }

}


bool isVariable(LinkedList_s * tokens, int startInd) {
    int i = startInd;

    int indSemicolon = indNextType(tokens, i, SEMICOLON);
    int indParen = indNextType(tokens, i, OPENPAREN);

    bool keepGoing = true;
    int indEquals = i;

    while (keepGoing) {
        indEquals = indNextType(tokens, indEquals, PUNCTUATION);
        struct Token * tempTok = getData_s(tokens, indEquals);
        if (tempTok->string[0] == '=' || indEquals == -1) {
            keepGoing = false;
        }
    }

    if (indSemicolon < indParen) {
        /*semicolon comes before, guaranteed variable */
        return true;
    } else {
        /* open paren first, possibly a function */
        /*could still be a variable with parenthesis */
        int indOpenBrace = indNextType(tokens, i, OPENBRACE);

        /* if the openbrace is before the semicolon it's a function */
        if (indOpenBrace < indSemicolon) {
            return false;
        } else {
            return true;
        }
    }
}


bool isFunction(LinkedList_s * tokens, int startInd) {
    int i = startInd;

    int indSemicolon = indNextType(tokens, i, SEMICOLON);
    int indParen = indNextType(tokens, i, OPENPAREN);

    bool keepGoing = true;
    int indEquals = i;

    while (keepGoing) {
        indEquals = indNextType(tokens, indEquals, PUNCTUATION);
        struct Token * tempTok = getData_s(tokens, indEquals);
        if (tempTok->string[0] == '=' || indEquals == -1) {
            keepGoing = false;
        }
    }

    if (indSemicolon < indParen) {
        /*semicolon comes before, guaranteed variable */
        return false;
    } else {
        /* open paren first, possibly a function */
        /*could still be a variable with parenthesis */
        int indOpenBrace = indNextType(tokens, i, OPENBRACE);

        /* if the openbrace is before the semicolon it's a function */
        if (indOpenBrace < indSemicolon) {
            return true;
        } else {
            return false;
        }
    }

}


char * delNReplace(char * origStr, int start, int len2Del, char * replaceStr) {
    int lenNewStr;
    int lenOldStr;
    int i;
    int deltaLen;
    char * newStr;

    for (i = 0; replaceStr[i] != '\0'; ++i) {
    } /* this gets the length of the given string to substitute into start */
    lenNewStr = i;

    /* length change of origString after deleting and inserting new*/
    deltaLen = lenNewStr - len2Del;
    /* negative numbers means shorter */

    /* malloc to make sure we have space for the new string */
    lenOldStr = strlen(origStr) + 1;
    newStr = malloc(lenOldStr + deltaLen);

    /*copy before the replace area */
    strncpy(newStr, origStr, start);
    newStr[start] = '\0'; /*copy in and terminate the string */

    /*copy in the replaceStr */
    strcat(newStr, replaceStr);

    /*copy the rest of the original string */
    strcat(newStr, origStr + start + len2Del);

    free(origStr);
    return newStr;

}


char * copyString(char * origStr, int start, int len2Cpy) {
    char * newStr = malloc(len2Cpy + 1);  /* +1 for \0 at end */
    int i;
    for (i = 0; i < len2Cpy && origStr[i+start] != '\0'; ++i) {
        /*copy wanted length or stop on overrun origStr */
        newStr[i] = origStr[i + start];
    }
    newStr[i] = '\0';
    return newStr;
}


void ll2String(LinkedList_s * tokens, int start, int end, char * buffer) {
    int i = 0;
    buffer[0] = '\0';
    for (i = start; i <= end; ++i) {
        struct Token * t = getData_s(tokens, i);
        strcat(buffer, t->string);
    }
}


bool isIdentChar(char character) {
    /*if it is alphanumeric or underscore it is an identifyer character */

    /*check for number
     * 48 = 0 in ascii, 57 = 9 in ascii */
    if (character >= '0' && character <= '9') {
        return true;
    } else if (character >= 'A' && character <= 'Z') {
        /*matches uppercase characters */
        return true;
    } else if (character >= 'a' && character <= 'z') {
        /*matches lowercase characters */
        return true;
    } else if (character == '_') {
        /* matches underscore character */
        return true;
    } else {
        return false;
    }
}


bool isWhitespace(char character) {
    if (character == '\n' || character == '\t' || character == ' ' || character == '\r') {
        return true;
    } else {
        return false;
    }
}


bool isClassToken(char * str) {
    return strmatch(str, "class");
}


bool strmatch(char * str1, char * str2) {
    int i;
    for (i = 0; str1[i] != '\0' && str2[i] != '\0'; ++i) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}


bool isNumber(char c) {
    if (c >= 48 && c <= 57) {
        return true;
    }
    return false;
}


bool isSpecial(char c) {
    if (c == ';' ||
            c == '(' ||
            c == ')' ||
            c == '{' ||
            c == '}' ||
            c == '[' ||
            c == ']' ||
            c == '.' ||
            c == ',' ||
            c == '*' ||
            c == '/' ||
            c == '-' ||
            c == '+' ||
            c == '\'' ||
            c == '"' ||
            c == '<' ||
            c == '>' ||
            c == '=' ||
            c == '&' ||
            c == '#' ||
            c == ';') {
        /* kill me */
        return true;
    } else {
        return false;
    }
}


enum TokenType getLastTypeExcludeWhitespace(LinkedList_s * tokenList, int curInd) {
    struct Token * lastToken;

    /*int i = length_s(tokenList) - 1; */
    int i = curInd;
    do {
        lastToken = (struct Token *) getData_s(tokenList, i--);
    } while (lastToken->type == WHITESPACE && i >= 0);
    return lastToken->type;
}


int indLastNotWhitespace(LinkedList_s * tokenList, int ind) {
    struct Token * lastToken;

    /*int i = length_s(tokenList) - 1; */
    int i = ind;
    do {
        lastToken = (struct Token *) getData_s(tokenList, i--);
    } while (lastToken->type == WHITESPACE && i >= 0);
    return i;
}

int indNextType(LinkedList_s * tokens, int startInd, enum TokenType type) {
    int i;
    struct Token * tok;
    for (i = startInd; i < length_s(tokens); ++i){
        tok = getData_s(tokens, i);
        if (tok->type == type) {
            return i;
        }
    }
    return -1;
}

int indPrevType(LinkedList_s * tokens, int startInd, enum TokenType type) {
    int i;
    struct Token * tok;
    for (i = startInd; i >= 0; --i){
        tok = getData_s(tokens, i);
        if (tok->type == type) {
            return i;
        }
    }
    return -1;
}

int indEndLast(LinkedList_s * tokens, int startInd) {
    int largest = -1;
    int indStartofTypeSemi = indPrevType(tokens, indName, SEMICOLON);
    int indStartofTypeOpenB = indPrevType(tokens, indName, OPENBRACE);
    int indStartofTypeCloseB = indPrevType(tokens, CLOSEBRACE);

    if (indStartofTypeSemi > largest) {
        largest = indStartofTypeSemi;
    }

    if (indStartofTypeOpenB > largest) {
        largest = indStartofTypeOpenB;
    }

    if (indStartofTypeCloseB > largest) {
        largest = indStartofTypeCloseB;
    }
    return largest;
}

enum TokenType getType(LinkedList_s * tokens, int ind) {
    struct Token * tok = getData_s(tokens, ind);
    return tok->type;
}
