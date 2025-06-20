/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:42:59 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/17 17:35:53 by ayaarab          ###   ########.fr       */
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

static char *absolute_path(char *cmd)
{
	char	*full;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	full = join_paths(".", cmd);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**path;
	char	*path_env;
	int		i;
	char	*full;

	if (!cmd || !*cmd)
		return (NULL);
	full = absolute_path(cmd);
	if (full)
		return (full);
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

void	exec_externals_in_child(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	path = get_cmd_path(cmd->cmd, env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	envp = list_to_env(env);
	execute_child_process(cmd, path, envp);
	free(path);
	free_2d_arr(envp);
}
