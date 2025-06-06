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

static void	handle_file_redirection(t_file *f)
{
    int	fd;

    fd = -1;
    if (f->type == TOKEN_REDIR_IN)
        fd = open(f->name, O_RDONLY);
    else if (f->type == TOKEN_REDIR_OUT)
        fd = open(f->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (f->type == TOKEN_APPEND)
        fd = open(f->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (f->type == TOKEN_HEREDOC)
    {
        if (f->h_fd != -1)
        {
            dup2(f->h_fd, STDIN_FILENO);
            close(f->h_fd);
            return;
        }
        else
            ft_putstr_fd("error in the heredoc\n", 2);
    }
    if (fd < 0)
        ft_putstr_fd("Error opening file: ", 2);
    else
    {
        dup2(fd, (f->type == TOKEN_REDIR_IN) ? STDIN_FILENO : STDOUT_FILENO);
        close(fd);
    }
}

void	apply_redirection(t_cmd *cmd)
{
	t_file	*f;

	f = cmd->file;
	while (f)
	{
		handle_file_redirection(f);
		f = f->next;
	}
}

static void	execute_child_process(t_cmd *cmd, char *path, char **envp)
{
    apply_redirection(cmd);
    set_signals_in_child();
    execve(path, cmd->args, envp);
    ft_putstr_fd("minishell: execve failed: ", 2);
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
		ft_putstr_fd("minishell: command not found", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 127;
		return ;
	}
	envp = list_to_env(env);
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, path, envp);
	else
	{
		waitpid(pid, &status, 0);
		update_exit_status(status);
	}
	free(path);
	free_2d_arr(envp);
}
