/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/08 16:07:11 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int ac, char **av, char **env)
{
	int			flag;
	char		*line;
	t_command	cmd;
	t_env		*new_env;

	(void)av;
	(void)ac;
	new_env = env_init(env);
	while (07)
	{
		line = readline("minishell :");
		if (!line)
			return (free_env(new_env), free(line), 2);
		check_unprint(&line);
		flag = check_quotes(line);
		if (flag)
			tokeniser(line, new_env, &cmd);
		free(line);
	}
	return (0);
}
