#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_FILES 100
#define BUFFER_SIZE 4096

int count_words_in_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return -1;
    }

    int word_count = 0;
    char word[BUFFER_SIZE];

    while (fscanf(fp, "%s", word) == 1) {
        word_count++;
    }

    fclose(fp);
    return word_count;
}

int count_words_in_string(const char *str) {
    int word_count = 0;
    int in_word = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            word_count++;
        }
    }
    
    return word_count;
}

int main(void) {
    printf("=== Word Counter with Pipes ===\n");
    printf("Enter file names (one per line), or strings starting with 'string:', or 'done' to finish:\n");
    
    char input[1024];
    char *files[MAX_FILES];
    char *strings[MAX_FILES];
    int file_count = 0;
    int string_count = 0;
    
    while (file_count + string_count < MAX_FILES) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "done") == 0) {
            break;
        }
        
        if (strncmp(input, "string:", 7) == 0) {
            strings[string_count] = strdup(input + 7);
            string_count++;
        } else {
            files[file_count] = strdup(input);
            file_count++;
        }
    }
    
    int total_tasks = file_count + string_count;
    
    if (total_tasks == 0) {
        printf("No tasks to process.\n");
        return 0;
    }
    
    printf("\nProcessing %d tasks (%d files, %d strings)...\n\n", 
           total_tasks, file_count, string_count);
    
    int total_words = 0;
    int pipefd[2];
    
    for (int i = 0; i < total_tasks; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) {
            close(pipefd[0]);
            
            int result;
            
            if (i < file_count) {
                result = count_words_in_file(files[i]);
            } else {
                result = count_words_in_string(strings[i - file_count]);
            }
            
            write(pipefd[1], &result, sizeof(result));
            close(pipefd[1]);
            
            exit(EXIT_SUCCESS);
        } else {
            close(pipefd[1]);
            
            int result;
            read(pipefd[0], &result, sizeof(result));
            close(pipefd[0]);
            
            int status;
            wait(&status);
            
            if (i < file_count) {
                if (result == -1) {
                    printf("Child %d (file '%s'): ERROR - File not found\n", i + 1, files[i]);
                } else {
                    printf("Child %d (file '%s'): %d words\n", i + 1, files[i], result);
                    total_words += result;
                }
            } else {
                printf("Child %d (string %d): %d words\n", i + 1, i - file_count + 1, result);
                total_words += result;
            }
        }
    }
    
    printf("\n=== FINAL RESULT ===\n");
    printf("Total word count: %d\n", total_words);
    
    for (int i = 0; i < file_count; i++) {
        free(files[i]);
    }
    for (int i = 0; i < string_count; i++) {
        free(strings[i]);
    }
    
    return 0;
}
