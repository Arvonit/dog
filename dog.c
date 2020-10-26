#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static FILE* file;
static bool show_line_numbers = false;
static bool read_from_stdin = false;

static void parse_argument(char *argument);

int main(int argc, char **argv)
{
    size_t buffer_size = 0;
    int line_number = 0;
    char *argument;
    char *line;

    // Must include at least one file name to continue
    if (argc < 2) {
        fprintf(stderr, "usage: dog [-n] [file ...]\n");
        exit(EXIT_FAILURE);
    }

    // Iterate through arguments
    for (int i = 1; i < argc; i++) {
        argument = argv[i];
        parse_argument(argument);
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
            if (!read_from_stdin && !show_line_numbers) {
                fprintf(stderr, "dog: %s: No such file or directory\n", argument);
            }
        }
    }
}

static void parse_argument(char *argument) 
{
    if (strcmp(argument, "-") == 0) {
        read_from_stdin = true;
    } else if (strcmp(argument, "-n") == 0) {
        show_line_numbers = true;
    } else {
        file = fopen(argument, "r");
    }
}
