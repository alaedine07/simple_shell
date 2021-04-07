#include "shell.h"
int check_builtins(char **command, char **envp);

/**
 * signal_handler - function that will handle the signal
 * @sig: sigint which is ctrl + c
 * Return:	print \n$ to next line
**/
void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n$ ");
		/* important never remove */
		fflush(stdout);
	}

}
/**
 * _exec_me - function that will execute command
 * @cmd: array of chars holding the command and arguments
 * Return:	void
**/
int _exec_me(char **cmd)
{
	if (fork() == 0)
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			perror("Error:");
			exit(127);
		}
	}
	wait(NULL);
	return (0);
}
/**
 * main - function that will initiate infinite input loop
 * @argc: number of arguments
 * @argv: array of arguments passed
 * @env: array of string hold the environment variables
 * Return:	check if the input is coming from terminal or not
 *			if the input is coming from terminal it will print $
 *			and trigger an infinite while loop that take user input
**/
int main(int argc, char **argv, char **env)
{
	size_t n = 0;
	char *lineptr;
	char **cmd;
	int int_mode = 5;
	int is_builtin;
	int is_path;
	int status;
	
	(void)argv;
	(void)argc;
	signal(SIGINT, signal_handler);
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode == 1)
		{
			printf("$ ");
		}
		getline(&lineptr, &n, stdin);
		/* without this entering just a new line will trigger a segfault */
		if (*lineptr == '\000')
		{
			printf("\n");
			exit(0);
		}
		if (*lineptr != '\n')
		{
			cmd = split_input(lineptr," \t\r\n");
			/* make a function that will check for alias, builtins, PATH */
			is_builtin = check_builtins(cmd, env);
			/* only fork and exec if the input is not a builtin command */
			if (is_builtin == -1)
			{
				/* if the command is not builtin check the command in PATH */
				is_path = check_path(lineptr, env);
				
			}
			/* if the command is neither in builtin and can't be added to PATH */
			if (is_path == -1 && is_builtin == -1)
			{
				status = _exec_me(cmd);
			}
			free(cmd);
		}
	}
	return (status);
}