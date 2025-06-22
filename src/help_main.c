#include "../includes/minishell.h"

void 	help(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		set_signals_in_child();
		apply_redirection(cmd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status);
}
