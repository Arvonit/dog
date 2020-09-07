#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *file;
    char *file_name;
    char file_char;

    // Must include one file name to continue
    if (argc < 2) {
        fprintf(stderr, "usage: dog [file]\n");
        exit(EXIT_FAILURE);
    }

    // Iterate through arguments
    for (int i = 1; i < argc; i++) {
        file_name = argv[i];

        file = fopen(file_name, "r");
        if (file) {
            while ((file_char = fgetc(file)) != EOF) {
                printf("%c", file_char);
            }
        } else {
            fprintf(stderr, "dog: %s: No such file or directory\n", file_name);
        }
        fclose(file);
    }
}
