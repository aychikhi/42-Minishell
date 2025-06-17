/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:05 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/13 17:46:03 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_heredoc(t_file *f)
{
	if (f->h_fd != -1)
	{
		dup2(f->h_fd, STDIN_FILENO);
		close(f->h_fd);
	}
}

static void	handle_redir(t_file *f)
{
	int	fd;

	fd = 0;
	if (f->type == TOKEN_REDIR_IN)
		fd = open(f->name, O_RDONLY);
	else if (f->type == TOKEN_REDIR_OUT)
		fd = open(f->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (f->type == TOKEN_APPEND)
		fd = open(f->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (f->type == TOKEN_HEREDOC)
	{
		handle_heredoc(f);
		return ;
	}
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(f->name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
		exit(1);
	}
	else
	{
		if (f->type == TOKEN_REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	apply_redirection(t_cmd *cmd)
{
	t_file	*f;

	f = cmd->file;
	while (f)
	{
		handle_redir(f);
		f = f->next;
	}
}

static void	execute_child_process(t_cmd *cmd, char *path, char **envp)
{
	set_signals_in_child();
	apply_redirection(cmd);
	execve(path, cmd->args, envp);
	ft_putstr_fd("minishell: execve failed: ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	exec_externals(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	path = get_cmd_path(cmd->cmd, env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found", 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 127;
		return ;
	}
	envp = list_to_env(env);
	execute_child_process(cmd, path, envp);
	free(path);
	free_2d_arr(envp);
	exit(EXIT_FAILURE);
}
