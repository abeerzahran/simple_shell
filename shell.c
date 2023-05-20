#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#define MAX_ARGS 10
/**
* main - PID
* Return: Always 0.
*/
int main(void)
{
char *args[2];
int status;
pid_t pid;
char *command;
size_t size = 100;
int i = 0;
while (1)
{_puts("#cisfun$ ");
fflush(stdout);
command = malloc(sizeof(char) * (size));
if (getline(&command, &size, stdin) == -1)
	{ break; }
while (command[i] != '\n' && command[i] != '\0')
	{ i++; }
command[i] = '\0';
args[0] = command;
args[1] = NULL;
pid = fork();
if (pid == 0)
{execve(command, args, NULL);
perror("./shell");
exit(EXIT_FAILURE); }
else if (pid < 0)
{ perror("fork"); }
else
{ waitpid(pid, &status, 0); }}
free(command);
return (0); }
