#include <token.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

    /* enters if on function failure */
    if (!tokenize(filename)) {
        puts("Could not tokenize file");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int tokenize(char * filename) {
    char buffer[512];
    FILE * inFP = fopen(filename, "r");

    if (inFP == NULL) {
        printf("Failed to open given file!\n");
        return RETURN_FAILURE;
    }

    /* read every line of the file */
    while(fgets(buffer, 512, inFP)) {
        enum lastPrintedType lpt = NONE;
        enum StringPrintingState sps = NOSTRING;
        char * currentChar = buffer;
        /* go over every character in the line */
        while(*currentChar != '\0') {

            switch(*currentChar) {
                /* for any whitespace, print a newline */
                case ' ':
                case '\t':
                case '\n':
                    if (sps == NOSTRING) {
                        if (lpt == CHARACTER) {
                            puts("");
                        }
                        lpt = WHITESPACE;
                    } else {
                        printf("%c", *currentChar);
                    }
                    break;
                    /* on any punctuation */
                case ',':
                    /* print the char, */
                case ';':
                    /* and a newline */
                case '(':
                case ')':
                case '{':
                case '}':
                    if (sps == NOSTRING) {
                        if (lpt == CHARACTER) {
                            puts("");
                        }
                        printf("%c\n", *currentChar);
                        lpt = PUNCTUATION;
                    } else {
                        printf("%c", *currentChar);
                    }
                    break;
                case '\'':
                    if (sps == NOSTRING) {
                        printf("\n%c", *currentChar);
                        sps = SINGLETICK;
                    } else if (sps == SINGLETICK) {
                        printf("%c\n", *currentChar);
                        sps = NOSTRING;
                    } else if (sps == DOUBLETICK) {
                        printf("%c", *currentChar);
                    }
                    break;
                case '\"':
                    if (sps == NOSTRING) {
                        printf("\n%c", *currentChar);
                        sps = DOUBLETICK;
                    } else if (sps == SINGLETICK) {
                        printf("%c", *currentChar);
                        /* TODO FIND A WAY TO HANDEL THIS */

                        /* WARNING WARNING TICK MISMATCH */

                    } else if (sps == DOUBLETICK) {
                        printf("%c\n", *currentChar);
                        sps = NOSTRING;
                    }
                    break;
                default:
                    printf("%c", *currentChar);
                    lpt = CHARACTER;
                    break;
            }

            /* must be the last line in the while loop */
            ++currentChar;
        }
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

















