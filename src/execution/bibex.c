/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bibex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:06:17 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/06 23:56:52 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_child_ctx
{
	t_cmd	*cur;
	t_env	*env;
	int		**pipes;
	int		i;
	int		cmd_count;
}			t_child_ctx;

typedef struct s_pipes_ctx
{
	int		cmd_count;
	int		**pipes;
	pid_t	*pids;
	t_cmd	*cur;
	int		i;
}			t_pipes_ctx;

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
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		update_exit_status(status);
		i++;
	}
}

static void	child_proc(t_child_ctx *ctx)
{
	set_signals_in_child();
	apply_redirection(ctx->cur);
	if (ctx->i != 0)
		dup2(ctx->pipes[ctx->i - 1][0], STDIN_FILENO);
	if (ctx->i != ctx->cmd_count - 1)
		dup2(ctx->pipes[ctx->i][1], STDOUT_FILENO);
	if (is_builtin(ctx->cur->cmd))
		exit(execute_builtin(ctx->cur, &ctx->env));
	exec_externals(ctx->cur, ctx->env);
	close_pipes(ctx->pipes, ctx->cmd_count - 1);
	exit(EXIT_FAILURE);
}

void	execute_pipeline(t_cmd *cmds, t_env *env)
{
	t_child_ctx	ctx;
	t_pipes_ctx	p_ctx;

	p_ctx.cmd_count = count_cmd(cmds);
	p_ctx.pipes = create_pipes(p_ctx.cmd_count - 1);
	p_ctx.pids = malloc(sizeof(pid_t) * p_ctx.cmd_count);
	p_ctx.cur = cmds;
	p_ctx.i = 0;
	while (p_ctx.cur)
	{
		ctx = (t_child_ctx){p_ctx.cur, env, p_ctx.pipes, p_ctx.i,
			p_ctx.cmd_count};
		p_ctx.pids[p_ctx.i] = fork();
		if (p_ctx.pids[p_ctx.i] == 0)
			child_proc(&ctx);
		p_ctx.cur = p_ctx.cur->next;
		p_ctx.i++;
	}
	close_pipes(p_ctx.pipes, p_ctx.cmd_count - 1);
	wait_all(p_ctx.pids, p_ctx.cmd_count);
	free_pipes(p_ctx.pipes, p_ctx.cmd_count - 1);
	free(p_ctx.pids);
}
