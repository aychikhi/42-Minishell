#include "../../includes/minishell.h"

int count_cmd(t_cmd *cmd)
{
	int count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return count;
}

static void close_pipes(int  **pipe, int count)
{
	int i = 0;
	while (i < count)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		i++;
	}
}
static int **create_pipes(int count)
{
	int **pipe = malloc(sizeof(int *) * count);
	int i =0;
	while (i < count)
	{
		pipe[i] = malloc(sizeof(int) * 2);
		if (!pipe[i])
		{
			ft_putstr_fd("minishell: malloc: allocation error\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return pipe;
}

void execute_pipeline(t_cmd *cmds, t_env *env)
{
	int cmd_count = count_cmd(cmds);
	int **pipes = create_pipes(cmd_count - 1);
	pid_t *pids = malloc(sizeof(pid_t) * cmd_count);
	t_cmd *current = cmds;
	int i = 0;

	while (current)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// Connect pipes
			if (i != 0) // not first
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i != cmd_count - 1) // not last
				dup2(pipes[i][1], STDOUT_FILENO);

			close_pipes(pipes, cmd_count - 1);
			apply_redirection(current); // if you have it

			if (is_builtin(current->cmd))
				exit(execute_builtin(current, &env));
			else
				exec_externals(current, env); // should call execve

			exit(EXIT_FAILURE);
		}
		current = current->next;
		i++;
	}

	close_pipes(pipes, cmd_count - 1);
	for (int j = 0; j < cmd_count; j++)
		waitpid(pids[j], NULL, 0);

	// Free pipes and pids
	for (int k = 0; k < cmd_count - 1; k++)
		free(pipes[k]);
	free(pipes);
	free(pids);
}
