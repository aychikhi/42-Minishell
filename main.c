/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/13 18:42:01 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_unprint(char **line)
{
	int i;
	int f;

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

void	kaynin_dquotes(char *line)
{
	int	i;
	int	f;
	
	f = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			f++;
		i++;
	}
	if (f % 2 != 0)
	{
		printf("Error!\n");
		exit(EXIT_FAILURE);
	}
}

void	kaynin_quotes(char *line)
{
	int	i;
	int	f;
	
	f = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			f++;
		i++;
	}
	if (f % 2 != 0)
	{
		printf("Error!\n");
		exit(EXIT_FAILURE);
	}
}

void	check_quotes(char **line)
{
	int i;

	kaynin_quotes(*line);
	kaynin_dquotes(*line);
	i = 0;
	while (line[0][i])
	{
		if (line[0][i] == '\'')
			line[0][i] = 31;
		else if (line[0][i] == '\"')
			line[0][i] = 30;
		i++;
	}
	line[0][i] = '\0';
}

void	one_space(char **line)
{
	int i;
	int f;
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
	t_cmd	*lst;

	(void)av;
	(void)ac;
	lst = NULL;
	while (1337)
	{
		line = readline("minishell :");
		check_unprint(&line);
		one_space(&line);
		check_quotes(&line);
		printf("%s\n", line);
	}
	return (0);
}



// static void	cleanup(t_cmd *lst, char *line)
// {
// 	t_cmd	*tmp;

// 	while (lst)
// 	{
// 		tmp = lst;
// 		lst = lst->next;
// 		free(tmp->cmd);
// 		free(tmp);
// 	}
// 	if (line)
// 		free(line);
// }

// int	main(int ac, char **av)
// {
// 	int		i;
// 	int		k;
// 	int		j;
// 	char	*cmd;
// 	char	*line;
// 	t_cmd	*lst;

// 	(void)av;
// 	(void)ac;
// 	lst = NULL;
// 	i = 0;
// 	j = 0;
// 	while (1337)
// 	{
// 		line = readline("minishell :");
// 		if (!line)
// 			break ;
// 		i = 0;
// 		while (line[i])
// 		{
// 			j = ft_isspecial(line, i);
// 			cmd = malloc(j + 1);
// 			if (!cmd)
// 				return (cleanup(lst, line), 1);
// 			k = 0;
// 			while (k < j)
// 			{
// 				cmd[k] = line[i + k];
// 				k++;
// 			}
// 			cmd[k] = '\0';
// 			if (!lst)
// 				lst = ft_lstnew(cmd);
// 			else
// 				ft_lstadd_back(&lst, ft_lstnew(cmd));
// 			i += j;
// 			if (line[i] == '|')
// 				i++;
// 		}
// 		t_cmd *tmp = lst;
// 		while (tmp)
// 		{
// 			printf("cmd->%s\n", (char *)tmp->cmd);
// 			tmp = tmp->next;
// 		}
// 		free(line);
// 		cleanup(lst, NULL);
// 		lst = NULL;
// 	}
// 	return (0);
// }