#include "../../includes/minishell.h"

static void	free_pipes(int **pipes, int count)
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

static void	wait_all(pid_t *pids, int count)
{
    int	i;
    int status;

    i = 0;
    while (i < count)
    {
        waitpid(pids[i], &status, 0);
        update_exit_status(status);
        i++;
    }
}

static void	child_proc(t_cmd *cur, t_env *env, int **pipes, int i, int cmd_count)
{
    set_signals_in_child();
    if (i != 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);
    if (i != cmd_count - 1)
        dup2(pipes[i][1], STDOUT_FILENO);
    close_pipes(pipes, cmd_count - 1);
    apply_redirection(cur);
    if (is_builtin(cur->cmd))
        exit(execute_builtin(cur, &env));
    exec_externals(cur, env);
    exit(EXIT_FAILURE);
}

void	execute_pipeline(t_cmd *cmds, t_env *env)
{
    int		cmd_count;
    int		**pipes;
    pid_t	*pids;
    t_cmd	*cur;
    int		i;

    cmd_count = count_cmd(cmds);
    collecting_heredoc(cmds);
    pipes = create_pipes(cmd_count - 1);
    pids = malloc(sizeof(pid_t) * cmd_count);
    cur = cmds;
    i = 0;
    while (cur)
    {
        pids[i] = fork();
        if (pids[i] == 0)
            child_proc(cur, env, pipes, i, cmd_count);
        cur = cur->next;
        i++;
    }
    close_pipes(pipes, cmd_count - 1);
    wait_all(pids, cmd_count);
    free_pipes(pipes, cmd_count - 1);
    free(pids);
}
