/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:29:15 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/22 12:29:15 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	help(t_cmd *cmd)
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
