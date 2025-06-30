/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bibex_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:05:00 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/30 21:15:20 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initialize_pipeline_resources(t_pipes_ctx *p_ctx, t_cmd *cmds)
{
	p_ctx->cmd_count = count_cmd(cmds);
	if (p_ctx->cmd_count <= 0)
		return (0);
	if (p_ctx->cmd_count == 1)
		p_ctx->pipes = NULL;
	else
	{
		p_ctx->pipes = create_pipes(p_ctx->cmd_count - 1);
		if (!p_ctx->pipes)
			return (0);
	}
	p_ctx->pids = malloc(sizeof(pid_t) * p_ctx->cmd_count);
	if (!p_ctx->pids)
	{
		ft_putstr_fd("minishell: malloc: allocation error\n", 2);
		g_exit_status = 1;
		if (p_ctx->pipes)
		{
			close_pipes(p_ctx->pipes, p_ctx->cmd_count - 1);
			free_pipes(p_ctx->pipes, p_ctx->cmd_count - 1);
		}
		return (0);
	}
	return (1);
}

void	execute_pipeline_commands(t_pipes_ctx *p_ctx, t_env *env, t_cmd *cmds)
{
	t_child_ctx	ctx;

	p_ctx->cur = cmds;
	p_ctx->i = 0;
	set_signals_for_child_execution();
	while (p_ctx->cur && p_ctx->i < p_ctx->cmd_count)
	{
		ctx.cur = p_ctx->cur;
		ctx.env = env;
		ctx.pipes = p_ctx->pipes;
		ctx.i = p_ctx->i;
		ctx.cmd_count = p_ctx->cmd_count;
		p_ctx->pids[p_ctx->i] = fork();
		if (p_ctx->pids[p_ctx->i] == 0)
			child_proc(&ctx);
		else if (p_ctx->pids[p_ctx->i] < 0)
		{
			ft_putstr_fd("minishell: fork failed\n", 2);
			g_exit_status = 1;
			break ;
		}
		p_ctx->cur = p_ctx->cur->next;
		p_ctx->i++;
	}
}

void	finalize_pipeline_execution(t_pipes_ctx *p_ctx)
{
	if (p_ctx->pipes)
		close_pipes(p_ctx->pipes, p_ctx->cmd_count - 1);
	if (p_ctx->i > 0)
		wait_all(p_ctx->pids, p_ctx->i);
	set_signals_interactive();
	cleanup_pipeline_resources(p_ctx);
}

void	cleanup_pipeline_resources(t_pipes_ctx *p_ctx)
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
