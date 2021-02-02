#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE* file;
    int line_number;
    char *argument;
    bool show_line_numbers = false;
    bool read_from_stdin = false;
    int failed_read_attempts = 0;

    // Iterate through arguments
    for (int i = 0; i < argc; i++) {
        // The 0th argument is the name of the program (i.e. dog), so if there are arguments,
        // increment the index. If there are no arguments, we will move on since we need to read
        // from standard input instead.
        if (i == 0 && argc > 1) {
            i++;
        }

        argument = argv[i];
        
        // TODO: Refactor this nasty conditional block
        if (argc < 2 || strcmp(argument, "-") == 0) {
            read_from_stdin = true;
            file = stdin;
        } else if (strcmp(argument, "-n") == 0 || strcmp(argument, "--number") == 0) {
            show_line_numbers = true;
            line_number = 1;
            continue;
        } else if (strcmp(argument, "--help") == 0) {
            fprintf(stderr, "Usage: dog [-n/--number] [file ...]\n");
            exit(EXIT_SUCCESS);
        } else if (strncmp(argument, "-", strlen("-")) == 0 ||
            strncmp(argument, "--", strlen("--")) == 0) {
            fprintf(stderr, "Usage: dog [-n/--number] [file ...]\n");
            exit(EXIT_FAILURE);
        } else {
            file = fopen(argument, "r");
        }

        // If file cannot be read, print an error and move to the next file
        if (!file) {
            fprintf(stderr, "dog: %s: No such file or directory\n", argument);
            failed_read_attempts += 1;
            continue;
        }
        
        // Collect current character to read file and previous character to determine the beginning
        // of a new line. We determine the beginning of a line if the previous character is a `\n`
        // or -1 (for the first line in the file; a bit of a hack).
        char curr_char;
        char prev_char = -1;

        // Read each character one-by-one in the file
        while ((curr_char = getc(file)) != EOF) {
            if (show_line_numbers && (prev_char == -1 || prev_char == '\n')) {
                printf("    %2i\t", line_number);
                line_number++;
            }

            printf("%c", curr_char);
            prev_char = curr_char;
        }

        // Only close files since standard input is not a file
        if (!read_from_stdin) {
            fclose(file);
        }
    }

    // Exit with failure if a file failed to be read
    if (failed_read_attempts == 0) {
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}