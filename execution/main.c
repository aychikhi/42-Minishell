/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:47 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/27 16:29:24 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	env_list = env_to_list(env);
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
			helper_builtins(line, &env_list);
		}
		free(line);
	}
	clear_history();
	return (g_exit_status);
}
