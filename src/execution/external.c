/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:05 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/21 18:25:42 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(t_file *f)
{
	if (f->h_fd != -1)
	{
		dup2(f->h_fd, STDIN_FILENO);
		close(f->h_fd);
	}
	else
		ft_putstr_fd("error in the heredoc\n", 2);
}

int	open_file_by_type(t_file *f)
{
	int	fd;

	if (f->type == TOKEN_REDIR_IN)
		fd = open(f->name, O_RDONLY);
	else if (f->type == TOKEN_REDIR_OUT)
		fd = open(f->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (f->type == TOKEN_APPEND)
		fd = open(f->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
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

void	execute_child_process(t_cmd *cmd, char *path, char **envp)
{
	set_signals_in_child();
	apply_redirection(cmd);
	execve(path, cmd->args, envp);
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putstr_fd(":command not found ", 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	exec_externals(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	char	*path;
	char	**envp;
	int		status;

	path = get_cmd_path(cmd->cmd, env);
	if (!path)
	{
		handle_path_not_found(cmd);
		return ;
	}
	envp = list_to_env(env);
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, path, envp);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		update_exit_status(status);
	}
	else
		handle_fork_error(path, envp);
	free(path);
	free_2d_arr(envp);
}
