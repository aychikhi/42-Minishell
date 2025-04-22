/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/22 13:05:08 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_fun(void)
{
	printf("Error !\n");
	exit(EXIT_FAILURE);
}



void	one_space(char **line)
{
	int	i;
	int	f;
	int	flag;

	i = 0;
	f = 0;
	flag = 0;
	while (line[0][f])
	{
		while (line[0][f] == ' ')
		{
			flag = 1;
			f++;
		}
		if (flag)
		{
			line[0][i] = ' ';
			flag = 0;
			i++;
		}
		line[0][i] = line[0][f];
		f++;
		i++;
	}
	line[0][i] = '\0';
}

int	main(int ac, char **av)
{
	char	*line;

	(void)av;
	(void)ac;
	while (1337)
	{
		line = readline("minishell :");
		check_unprint(&line);
		one_space(&line);
		check_quotes(line);
		free (line);
		// printf("%s\n", line);
	}
	return (0);
}
