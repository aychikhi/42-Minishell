/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/10 15:09:16 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
	int		i;
	int		j;
	char	*line;
	char	*cmd;

	if (ac > 1)
	{
		i = 0;
		while (i < ac)
		{	
			line = readline(av[i]);
			i++;
		}
		i = 0;
		while (1)
		{			
			j = ft_isspecial(line);
			if (!j)
				break;
			cmd = malloc ((j - i) + 1);
			i = 0;
			while (i < j)
			{
				cmd[i] = line[j];
				j++;
				i++;
			}
			printf("%s\n", cmd);
			free (cmd);
			i = j;
		}
	}
	return (0);
}
