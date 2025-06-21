/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:55:14 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/21 18:25:44 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	run_builtin(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd->args);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd->args, env);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		g_exit_status = ft_pwd();
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		g_exit_status = ft_env(*env);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd->args);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(cmd->args, env);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd->args, env);
	else
	{
		// ft_putstr_fd("minishell: command not found ", 2);
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(":command not found ", 2);
		g_exit_status = 127;
	}
}

int	execute_builtin(t_cmd *cmd, t_env **env)
{
	int	stdin_copy;
	int	stdout_copy;

	if (!cmd || !cmd->cmd)
		return (1);
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	apply_redirection(cmd);
	run_builtin(cmd, env);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (g_exit_status);
}
