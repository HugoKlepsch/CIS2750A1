#include <tokenizer.h>
#include <stdlib.h>
#include <stdio.h>

int tokenize(char * filename);


int main(int argc, char ** argv) {
    char filename[50];

    if (argc != 2) { //needs one arg of the filename
        printf("needs to be run with filename!\n");
        return EXIT_FAILURE;
    }

    strncpy(filename, argv[0], 30);
    filename[29] = '\0'; //assuring that the filename is null-terminated



}


int tokenize(char * filename) {
    char buffer[512];
    FILE * inFP = fopen(filename, "r");
    if (inFP == NULL) {
        printf("Failed to open given file!\n");
        return EXIT_FAILURE;
    }

    while(fgets(buffer, 512, inFP)) { //read every line of the file
        while(*buffer != '\0') { //go over every character in the line

            ++buffer;
        }
    }

}
