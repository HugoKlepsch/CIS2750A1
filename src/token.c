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
}


int main(int argc, char ** argv) {
    char filename[100];

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
    if (tokenize(filename, &tokens) == RETURN_FAILURE) {
        /*failed to tokenize file*/
        printf("Failed to tokenize file\n");
        destroyList_s(&tokens, &freeToken);
        return EXIT_FAILURE;
    }


    destroyList_s(&tokens, &freeToken);
    return EXIT_SUCCESS;
}


struct Token * makeToken(char * string, enum TokenType type) {
    struct Token * newToken;
    newToken = malloc(sizeof(*newToken));
    newToken->string = string;
    newToken->type = type;
    return newToken;
}


void freeToken(void * token) {
    struct Token * givenToken = (struct Token *) token;
    free(givenToken->string);
    free(givenToken);
}


int tokenize(char * filename, LinkedList_s * tokenList) {
    char buffer[512];
    FILE * inFP = fopen(filename, "r");

    if (inFP == NULL) {
        printf("Failed to open given file!\n");
        return RETURN_FAILURE;
    }

    /* read every line of the file */
    while(fgets(buffer, 512, inFP)) {
    }
    fclose(inFP);
    return RETURN_SUCCESS;

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

















