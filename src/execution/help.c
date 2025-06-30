/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:10:26 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/30 21:46:35 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	cleanup_pipes_on_error(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static int	**allocate_pipes_array(int count)
{
	int	**pipes;

	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
	{
		g_exit_status = 1;
	}
	return (pipes);
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	if (count <= 0)
		return (NULL);
	pipes = allocate_pipes_array(count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
		{
			if (pipes[i])
				free(pipes[i]);
			cleanup_pipes_on_error(pipes, i);
			g_exit_status = 1;
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
