/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals_help1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:41:20 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/21 18:25:43 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_fork_error(char *path, char **envp)
{
	ft_putstr_fd("minishell: fork failed\n", 2);
	g_exit_status = 1;
	free(path);
	free_2d_arr(envp);
}

void	handle_path_not_found(t_cmd *cmd)
{
	if (access(cmd->cmd, F_OK) == 0)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 126;
		return ;
	}
	else
	{
		// ft_putstr_fd("minishell: command not found ", 2);
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(":command not found ", 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 127;
	}
}

static void	handle_file_error_and_exit(t_file *f)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(f->name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_status = 1;
	exit(1);
}

void	handle_redir(t_file *f)
{
	int	fd;

	if (f->type == TOKEN_HEREDOC)
	{
		handle_heredoc(f);
		return ;
	}
	fd = open_file_by_type(f);
	if (fd < 0)
		handle_file_error_and_exit(f);
	else
	{
		if (f->type == TOKEN_REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
