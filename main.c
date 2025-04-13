/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/13 11:13:51 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup(t_cmd *lst, char *line)
{
	t_cmd	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->cmd);
		free(tmp);
	}
	if (line)
		free(line);
}

int	main(int ac, char **av)
{
	int		i;
	int		k;
	int		j;
	char	*cmd;
	char	*line;
	t_cmd	*lst;

	(void)av;
	(void)ac;
	lst = NULL;
	i = 0;
	j = 0;
	while (1337)
	{
		line = readline("minishell :");
		if (!line)
			break ;
		i = 0;
		while (line[i])
		{
			j = ft_isspecial(line, i);
			cmd = malloc(j + 1);
			if (!cmd)
				return (cleanup(lst, line), 1);
			k = 0;
			while (k < j)
			{
				cmd[k] = line[i + k];
				k++;
			}
			cmd[k] = '\0';
			if (!lst)
				lst = ft_lstnew(cmd);
			else
				ft_lstadd_back(&lst, ft_lstnew(cmd));
			i += j;
			if (line[i] == '|')
				i++;
		}
		free(line);
		cleanup(lst, NULL);
		lst = NULL;
	}
	return (0);
}
		// t_cmd *tmp = lst;
		// while (tmp)
		// {
		// 	printf("cmd->%s\n", (char *)tmp->cmd);
		// 	tmp = tmp->next;
		// }