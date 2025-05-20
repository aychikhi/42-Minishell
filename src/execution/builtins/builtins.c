/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:55:14 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/27 16:45:38 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static void	handle_builtin(char **args, t_env **env)
// {
// 	if (ft_strncmp(args[0], "echo", 5) == 0)
// 		ft_echo(args);
// 	else if (ft_strncmp(args[0], "cd", 3) == 0)
// 		ft_cd(args, env);
// 	else if (ft_strncmp(args[0], "pwd", 4) == 0)
// 		g_exit_status = ft_pwd();
// 	else if (ft_strncmp(args[0], "env", 4) == 0)
// 		g_exit_status = ft_env(*env);
// 	else if (ft_strncmp(args[0], "exit", 5) == 0)
// 		ft_exit(args);
// 	else if (ft_strncmp(args[0], "export", 7) == 0)
// 		ft_export(args, env);
// 	else if (ft_strncmp(args[0], "unset", 6) == 0)
// 		ft_unset(args, env);
// 	else
// 		fprintf(stderr, "minishell: %s: command not found\n", args[0]);
// }

// void print_args(char **args)
// {
//     for (int i = 0;args[i]; i++)
//         printf("args %d, %s\n", i+1, args[i]);
// }

void execute_builtin(t_cmd *cmd, t_env **env)
{
    if (!cmd || !cmd->cmd) 
        return;
    // printf("cmd %s , args %s \n",cmd->cmd , cmd->args[0]);
    // print_args(cmd->args);
    if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
        ft_echo(cmd->args);
    else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
        ft_cd(cmd->args, env);
    else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
        g_exit_status = ft_pwd();
    else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
        g_exit_status = ft_env(*env);
    else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
        ft_exit(cmd->args);
    else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
        ft_export(cmd->args, env);
    else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
        ft_unset(cmd->args, env);
    else
        ft_putstr_fd("minishell: command not found\n", 2);
}
// void	helper_builtins(char *cmd, t_env **env)
// {
// 	char	**args;
// 	int		i;

// 	args = ft_split(cmd, ' ');
// 	if (!args || !args[0])
// 	{
// 		free(args);
// 		return ;
// 	}
// 	handle_builtin(args, env);
// 	i = 0;
// 	while (args[i])
// 		free(args[i++]);
// 	free(args);
// }
