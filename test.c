#include <tokenizer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
        char * currentChar = buffer;
        while(*currentChar != '\0') { //go over every character in the line
            switch(*currentChar) {
                case ' ': //for any whitespace, print a newline
                case '\t':
                case '\n':
                    puts("");
                    break;
                case ',': //on any punctuation
                case ';': //print the char,
                case '(': //and a newline
                case ')':
                case '{':
                case '}':
                    printf("%c\n", *currentChar);
                    break;
                default:
                    printf("%c", *currentChar);
                    break;
            }
            ++currentChar; //must be the last line in the while loop
        }
    }
    fclose(inFP);
    return RETURN_SUCCESS;
}
