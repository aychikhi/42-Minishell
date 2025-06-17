#include "../../includes/minishell.h"

void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	wait_all(pid_t *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		update_exit_status(status);
		i++;
	}
}