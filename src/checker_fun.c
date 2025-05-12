/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:05:10 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/24 15:00:39 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (line[i])
	{
		if (flag == 1 && line[i] == '\'')
			return (i + 1);
		else if (flag == 2 && line[i] == '\"')
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_quotes(char *line)
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
				return (error_fun());
			f = 0;
			i += j;
		}
		else
			i++;
	}
	return (1);
}
