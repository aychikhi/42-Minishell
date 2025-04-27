/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:55:14 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/27 15:58:01 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	handle_builtin(char **args, char **env)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
	{
	}
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		g_exit_status = ft_pwd();
	else if (ft_strncmp(args[0], "env", 4) == 0)
		g_exit_status = ft_env(env);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		ft_exit(args);
	else if (ft_strncmp(args[0], "export", 7) == 0)
	{
	}
	else if (ft_strncmp(args[0], "unset", 6) == 0)
	{
	}
	else
		fprintf(stderr, "minishell: %s: command not found\n", args[0]);
}

void	helper_builtins(char *cmd, char **env)
{
	char	**args;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		free(args);
		return ;
	}
	handle_builtin(args, env);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}
