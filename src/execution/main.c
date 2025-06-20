/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:47 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/06 22:53:46 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			g_exit_status;

int	is_builtin(char *cmd)
{
	if (!cmd)
		exit(0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"));
}

static void	execute_command(t_command *cmd, t_env **env_list)
{
	if (collecting_heredoc(cmd->cmd, *env_list))
		return;
	if (cmd->cmd && cmd->cmd->next)
		execute_pipeline(cmd->cmd, *env_list);
	else if (cmd->cmd)
	{
		if (is_builtin(cmd->cmd->cmd))
			execute_builtin(cmd->cmd, env_list);
		else
			exec_externals(cmd->cmd, *env_list);
	}
}

static void	process_line(char *line, t_env **env_list)
{
	t_command	cmd;

	if (*line)
	{
		add_history(line);
		tokeniser(line, *env_list, &cmd);
		if (cmd.cmd != NULL)
			execute_command(&cmd, env_list);
		if (cmd.cmd)
			free_cmd(cmd.cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	env_list = env_to_list(env);
	set_signals_interactive();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			exit(g_exit_status);
		}
		process_line(line, &env_list);
		free(line);
	}
	clear_history();
	free_env(env_list);
	return (g_exit_status);
}
