#include <unistd.h>

void echo(char **args)
{
	int i = 0;
	while (args[i] != NULL)
	{
		write(1, args[i], sizeof(args[i]));
		write(1, "\n", 1);
		i++;
	}
}