/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:10:26 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/30 15:01:34 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_fun(void)
{
	ft_putstr_fd("Error: Unclosed quotes!\n", 2);
	g_exit_status = 258;
	return (0);
}

void	malloc_error(void)
{
	printf("malloc Error !\n");
	exit(EXIT_FAILURE);
}

int	count_cmd(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	close_pipes(int **pipe, int count)
{
	int	i;

	if (!pipe)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipe[i])
		{
			close(pipe[i][0]);
			close(pipe[i][1]);
		}
		i++;
	}
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	if (count <= 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
	{
		ft_putstr_fd("minishell: malloc: allocation error\n", 2);
		g_exit_status = 1;
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			ft_putstr_fd("minishell: malloc: allocation error\n", 2);
			g_exit_status = 1;
			return (NULL);
		}
		if (pipe(pipes[i]) < 0)
		{
			free(pipes[i]);
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			ft_putstr_fd("minishell: pipe: allocation error\n", 2);
			g_exit_status = 1;
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
