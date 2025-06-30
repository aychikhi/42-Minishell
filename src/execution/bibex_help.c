/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bibex_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:40:52 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/30 15:00:13 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			free(pipes[i]);
			pipes[i] = NULL;
		}
		i++;
	}
	free(pipes);
}

void	wait_all(pid_t *pids, int count)
{
	int	i;
	int	status;

	if (!pids || count <= 0)
		return ;
	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			update_exit_status(status);
		}
		i++;
	}
}
