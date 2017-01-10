#include <tokenizer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>



int main(int argc, char ** argv) {
    char filename[100];

    if (argc != 2) { //needs one arg of the filename
        printf("needs to be run with filename!\n");
        return EXIT_FAILURE;
    }

    strncpy(filename, argv[1], 100);
    filename[99] = '\0'; //assuring that the filename is null-terminated

    if (!tokenize(filename)) { //enters if body on function failure
        puts("Could not tokenize file");
        return EXIT_FAILURE;
    }

}


int tokenize(char * filename) {
    char buffer[512];
    FILE * inFP = fopen(filename, "r");

    if (inFP == NULL) {
        printf("Failed to open given file!\n");
        return RETURN_FAILURE;
    }

    while(fgets(buffer, 512, inFP)) { //read every line of the file
        enum lastPrintedType lpt = NONE;
        enum StringPrintingState sps = NOSTRING;
        char * currentChar = buffer;
        while(*currentChar != '\0') { //go over every character in the line

            switch(*currentChar) {
                case ' ': //for any whitespace, print a newline
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
                case ',': //on any punctuation
                case ';': //print the char,
                case '(': //and a newline
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
                        //TODO FIND A WAY TO HANDEL THIS
                        //WARNING WARNING TICK MISMATCH
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

            ++currentChar; //must be the last line in the while loop
        }
    }
    fclose(inFP);
    return RETURN_SUCCESS;

}











