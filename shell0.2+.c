#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

#define MAX_ARGS 10

int main(void)
{
    char *command = NULL;
    size_t command_size = 0;
    ssize_t input_length;
    size_t arg_count = 0;
    pid_t pid;
    char *token;
    char **args;

    while (1)
    {
        _puts("#cisfun$ ");
        fflush(stdout);

        input_length = getline(&command, &command_size, stdin);
        if (input_length == -1)
        {
            break;
        }

        if (command[0] == '\n')
            continue;

        args = malloc(sizeof(char *) * (MAX_ARGS + 1));
        if (!args)
        {
            perror("./shell");
            exit(EXIT_FAILURE);
        }

        command[input_length - 1] = '\0';
        token = strtok(command, " ");
        while (token != NULL && arg_count < MAX_ARGS)
        {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        // Search for executable in PATH
        char *path = getenv("PATH");
        if (path == NULL)
        {
            perror("getenv");
            exit(EXIT_FAILURE);
        }

        char *path_token = strtok(path, ":");
        while (path_token != NULL)
        {
            char executable_path[100];
            snprintf(executable_path, sizeof(executable_path), "%s/%s", path_token, args[0]);
            execve(executable_path, args, NULL);
            path_token = strtok(NULL, ":");
        }

        // If the loop completes, executable was not found
        perror("./shell");
        exit(EXIT_FAILURE);

        arg_count = 0;
        free(args);
    }

    free(command);
    return 0;
}
