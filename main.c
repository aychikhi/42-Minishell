/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/22 11:54:47 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_fun(void)
{
	printf("Error !\n");
	exit(EXIT_FAILURE);
}

void	check_unprint(char **line)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (line[0][f])
	{
		if (line[0][f] >= 1 && line[0][f] <= 31)
			f++;
		else
		{
			line[0][i] = line[0][f];
			f++;
			i++;
		}
	}
	line[0][i] = '\0';
}

int	skip_fun(char *line, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
		line[i - 1] = 31;
	else
		line[i - 1] = 30;
	while (line[i])
	{
		if (flag == 1 && line[i] == '\'')
		{
			line[i] = 31;
			return (i + 1);
		}
		else if (flag == 2 && line[i] == '\"')
		{
			line[i] = 30;
			return (i + 1);
		}
		i++;
	}
	return (0);
}

void	check_quotes(char *line)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	f = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !f)
		{
			f = 1;
			if (line[i] == '\"')
				f++;
			i++;
			j = skip_fun(line + i, f);
			if (j == 0)
				error_fun();
			f = 0;
			i += j;
		}
		else
			i++;
	}
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
		// printf("%s\n", line);
	}
	return (0);
}
