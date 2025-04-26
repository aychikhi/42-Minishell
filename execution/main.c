/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:47 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/18 17:00:10 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int g_exit_status = 0;

//TODO handle the signal ctrl+C and exit
//signals to handl SIGINT, SIGQUIT

// void	signal_handler(int sig)
// {
// }


// builins helper

void helper(char *cmd, char **env)
{
    char **args = ft_split(cmd, ' ');

    if (!args || !args[0])
    {
        free(args);
        return;
    }

    if (ft_strncmp(args[0], "echo", 5) == 0)
        g_exit_status = ft_echo(args);
    else if (ft_strncmp(args[0], "cd", 3) == 0)
        {
			// ft_cd(args, env); // Implement ft_cd
		}
    else if (ft_strncmp(args[0], "pwd", 4) == 0)
        g_exit_status = ft_pwd();
    else if (ft_strncmp(args[0], "env", 4) == 0)
		g_exit_status = ft_env(env);
    else if (ft_strncmp(args[0], "exit", 5) == 0)
        ft_exit(args);
    else if (ft_strncmp(args[0], "export", 7) == 0)
        {
			// ft_export(args, env); // Implement ft_export
		}
    else if (ft_strncmp(args[0], "unset", 6) == 0)
        {
			// ft_unset(args, env); // Implement ft_unset
		}
    else
        fprintf(stderr, "minishell: %s: command not found\n", args[0]);

    int  i = 0;
    while (args[i])
        free(args[i++]);
    free(args);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	char	*line;
	
	
	g_exit_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
		{
			helper(line , env);
			add_history(line);
		}
		free(line);
	}
	return (0);
}
