/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bibex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:06:17 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/30 14:59:54 by aychikhi         ###   ########.fr       */
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

static void	setup_pipe_redirection(t_child_ctx *ctx)
{
	if (ctx->i != 0 && ctx->pipes)
	{
		dup2(ctx->pipes[ctx->i - 1][0], STDIN_FILENO);
		close(ctx->pipes[ctx->i - 1][0]);
	}
	if (ctx->i != ctx->cmd_count - 1 && ctx->pipes)
	{
		dup2(ctx->pipes[ctx->i][1], STDOUT_FILENO);
		close(ctx->pipes[ctx->i][1]);
	}
}

static void	close_unused_pipes(t_child_ctx *ctx)
{
	int	i;

	if (!ctx->pipes)
		return ;
	i = 0;
	while (i < ctx->cmd_count - 1)
	{
		if (i != ctx->i - 1)
			close(ctx->pipes[i][0]);
		if (i != ctx->i)
			close(ctx->pipes[i][1]);
		i++;
	}
}

static void	child_proc(t_child_ctx *ctx)
{
	g_exit_status = 0;
	set_signals_in_child();
	apply_redirection(ctx->cur);
	close_unused_pipes(ctx);
	setup_pipe_redirection(ctx);
	if (is_builtin(ctx->cur->cmd))
		exit(execute_builtin(ctx->cur, &ctx->env));
	exec_externals_in_child(ctx->cur, ctx->env);
	exit(EXIT_FAILURE);
}

static void	cleanup_pipeline_resources(t_pipes_ctx *p_ctx)
{
	if (p_ctx->pipes)
	{
		close_pipes(p_ctx->pipes, p_ctx->cmd_count - 1);
		free_pipes(p_ctx->pipes, p_ctx->cmd_count - 1);
		p_ctx->pipes = NULL;
	}
	if (p_ctx->pids)
	{
		free(p_ctx->pids);
		p_ctx->pids = NULL;
	}
}

void	execute_pipeline(t_cmd *cmds, t_env *env)
{
	t_child_ctx	ctx;
	t_pipes_ctx	p_ctx;

	p_ctx.cmd_count = count_cmd(cmds);
	if (p_ctx.cmd_count <= 0)
		return ;
	if (p_ctx.cmd_count == 1)
		p_ctx.pipes = NULL;
	else
	{
		p_ctx.pipes = create_pipes(p_ctx.cmd_count - 1);
		if (!p_ctx.pipes)
			return ;
	}
	p_ctx.pids = malloc(sizeof(pid_t) * p_ctx.cmd_count);
	if (!p_ctx.pids)
	{
		ft_putstr_fd("minishell: malloc: allocation error\n", 2);
		g_exit_status = 1;
		if (p_ctx.pipes)
		{
			close_pipes(p_ctx.pipes, p_ctx.cmd_count - 1);
			free_pipes(p_ctx.pipes, p_ctx.cmd_count - 1);
		}
		return ;
	}
	p_ctx.cur = cmds;
	p_ctx.i = 0;
	set_signals_for_child_execution();
	while (p_ctx.cur && p_ctx.i < p_ctx.cmd_count)
	{
		ctx = (t_child_ctx){p_ctx.cur, env, p_ctx.pipes, p_ctx.i,
			p_ctx.cmd_count};
		p_ctx.pids[p_ctx.i] = fork();
		if (p_ctx.pids[p_ctx.i] == 0)
			child_proc(&ctx);
		else if (p_ctx.pids[p_ctx.i] < 0)
		{
			ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
			g_exit_status = 1;
			break ;
		}
		p_ctx.cur = p_ctx.cur->next;
		p_ctx.i++;
	}
	if (p_ctx.pipes)
		close_pipes(p_ctx.pipes, p_ctx.cmd_count - 1);
	if (p_ctx.i > 0)
		wait_all(p_ctx.pids, p_ctx.i);
	set_signals_interactive();
	cleanup_pipeline_resources(&p_ctx);
}
