/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:47 by ayaarab           #+#    #+#             */
/*   Updated: 2025/05/22 18:47:56 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			g_exit_status;

int	error_fun(void)
{
	printf("Error: Unclosed quotes!\n");
	return (0);
}

void	malloc_error(void)
{
	printf("malloc Error !\n");
	exit(EXIT_FAILURE);
}
static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_exit_status = 131;
	}
}

static int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
			!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env") ||
			!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export") ||
			!ft_strcmp(cmd, "unset"));
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_env		*env_list;
	t_command	cmd;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	env_list = env_to_list(env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokeniser(line, env_list, &cmd);
			if (cmd.cmd != NULL)
			{
				if (is_builtin(cmd.cmd->cmd))
					execute_builtin(cmd.cmd, &env_list);
				else
					exec_externals(cmd.cmd, env_list);
			}
			if (cmd.cmd)
				free_cmd(cmd.cmd);
		}
		free(line);
	}
	clear_history();
	free_env(env_list);
	return (g_exit_status);
}
