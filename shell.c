#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/**
* main - PID
* Return: Always 0.
*/
int main(void)
{
char *command = NULL;
size_t command_size = 0;
ssize_t input_length;
char *args[2];
pid_t pid;
while (1)
{
printf("#cisfun$ ");
fflush(stdout);
input_length = getline(&command, &command_size, stdin);
if (input_length == -1)
{
break;
}
if (command[0] == '\n')
continue;
command[input_length - 1] = '\0';
args[0] = command;
args[1] = NULL;
pid = fork();
if (pid == 0)
{
execve(command, args, NULL);
perror("Error");
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
	perror("fork");
}
else
{
waitpid(pid, NULL, 0);
}
}
free(command);
return (0);
}
