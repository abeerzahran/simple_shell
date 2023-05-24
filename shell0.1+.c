#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_ARGS 10
/**
* main - PID
* Return: Always 0.
*/
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
printf("#cisfun$ ");
fflush(stdout);
input_length = getline(&command, &command_size, stdin);
if (input_length == -1)
{ break; }
if (command[0] == '\n')
continue;
args = malloc(sizeof(char *) * (MAX_ARGS + 1));
if (!args)
{ perror("./shell");
exit(EXIT_FAILURE); }
command[input_length - 1] = '\0';
token = strtok(command, " ");
while (token != NULL && arg_count < MAX_ARGS)
{ args[arg_count++] = token;
token = strtok(NULL, " "); }
args[arg_count] = NULL;
pid = fork();
if (pid == 0)
{ execve(args[0], args, NULL);
perror("./shell");
exit(EXIT_FAILURE); }
else if (pid < 0)
{ perror("fork"); }
else
{ waitpid(pid, NULL, 0); }
arg_count = 0;
free(args); }
free(command);
return (0); }
