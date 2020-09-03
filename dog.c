#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file;
    char *file_name = argv[1];
    char file_char;

    if (argc != 2) {
        fprintf(stderr, "usage: dog [file]\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(file_name, "r");
    while ((file_char = fgetc(file)) != EOF) {
        printf("%c", file_char);
    }
    fclose(file);
    
    exit(EXIT_SUCCESS);
}
