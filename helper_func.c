#include "shell.h"
/**
 * _strncmp - compares two strings
 * @s1: first string, of two, to be compared in length
 * @s2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int _strncmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}
/**
 * _strlen - returns the length of a string
 * @s: string to be measured
 * Return: length of string
 */
unsigned int _strlen(char *s)
{
	unsigned int len;

	len = 0;

	for (len = 0; s[len]; len++)
		;
	return (len);
}
/**
 * free_array - free an array of strings
 * @array: array of strings
 * Return: void
**/
void free_array(char **array)
{
	int i;

	for (i = 0; array[i]; i++)
	{
		free(array[i]);
	}
	free(array);
}
/**
 * find_path - function that extacts the PATH variable.
 * Return: string that holds the environment variable PATH.
*/
char *find_path()
{
	char *path = "PATH=";
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < 5 ; j++)
		{
			if (path[j] != environ[i][j])
			{
				break;
			}
			if (j == 4)
			{
				return (environ[i]);
			}
		}
	}
	return (NULL);
}
