/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:05 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/06 18:06:37 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_paths(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**path;
	char	*path_env;
	int		i;
	char	*full;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	i = 0;
	path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		full = join_paths(path[i], cmd);
		if (access(full, X_OK) == 0)
		{
			free_2d_arr(path);
			return (full);
		}
		free(full);
		i++;
	}
	free_2d_arr(path);
	return (NULL);
}

void	apply_redirection(t_cmd *cmd)
{
	t_file	*f;
	int		fd;

	f = cmd->file;
	while (f)
	{
		if (f->type == TOKEN_REDIR_IN)
		{
			fd = open(f->name, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else if (f->type == TOKEN_REDIR_OUT)
		{
			fd = open(f->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (f->type == TOKEN_APPEND)
		{
			fd = open(f->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (f->type == TOKEN_HEREDOC)
		{
			printf("[DEBUG] Processing heredoc for file: %d\n", f->h_fd);
			if (f->h_fd != -1)
			{
				dup2(f->h_fd, STDIN_FILENO);
				close(f->h_fd);
			}
			else
				ft_putstr_fd("error in the heredoc\n", 2);
		}
		if (fd < 0)
			ft_putstr_fd("Error opening file: ", 2);
		else
			close(fd);
		f = f->next;
	}
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
		ft_putstr_fd("minishell: command not found", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 127;
		return ;
	}
	envp = list_to_env(env);
	pid = fork();
	if (pid == 0)
	{
		apply_redirection(cmd);
		set_signals_in_child();
		execve(path, cmd->args, envp);
		ft_putstr_fd("minishell: execve failed: ", 2);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		update_exit_status(status);
	}
	free(path);
	free_2d_arr(envp);
}
