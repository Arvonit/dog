#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    size_t buffer_size = 0;
    int line_number = 0;
    FILE *file;
    char *file_name;
    char *line;
    // TODO: Implement support for flags
    bool show_line_numbers = false;

    // TODO: Implement support for reading from the standard input (i.e. `-`)
    // Must include at least one file name to continue
    if (argc < 2) {
        fprintf(stderr, "usage: dog [file ...]\n");
        exit(EXIT_FAILURE);
    }

    // Iterate through arguments
    for (int i = 1; i < argc; i++) {
        file_name = argv[i];
        file = fopen(file_name, "r");
        if (file) {
            if (show_line_numbers) {
                line_number = 0;
            }
            while (getline(&line, &buffer_size, file) != -1) {
                if (show_line_numbers) {
                    line_number++;
                    printf("    %2i\t", line_number);
                }
                printf("%s", line);
            }
            fclose(file);
        } else {
            fprintf(stderr, "dog: %s: No such file or directory\n", file_name);
        }
    }
}
