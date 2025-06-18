/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:10:26 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/06 23:54:46 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_fun(void)
{
	printf("Error: Unclosed quotes!\n");
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

	i = 0;
	while (i < count)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		i++;
	}
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * count);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			ft_putstr_fd("minishell: malloc: allocation error\n", 2);
			exit(EXIT_FAILURE);
		}
		if (pipe(pipes[i]) < 0)
		{
			ft_putstr_fd("minishell: pipe: allocation error\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}
