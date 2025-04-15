#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>

int	main(int ac , char **args , char **envp)
{
	int pid = fork();
	printf("%d",pid);
	if (pid > 0)
	{
		execve("/bin/ls", args, envp);
		printf("%d\n",pid);
	}
	else
	{
		printf("%d",pid);
		wait(NULL);
	}
}