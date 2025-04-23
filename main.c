/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/23 13:51:54 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_fun(void)
{
	printf("Error: Unclosed quotes!\n");
	exit(EXIT_FAILURE);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
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

static void	print_token(t_token *tokens)
{
	t_token	*tmp;
	
	tmp = tokens;
	while (tmp)
	{
		printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

t_env	*env_init(char **env)
{
	t_env	*new_env;
	t_env	*last;
	t_env	*new_node;
	int		i;

	new_env = NULL;
	last = NULL;
	if (!env || !*env)
		return (NULL);
	new_env = ft_lstnew(extract_var(env[0]), extract_value(env[0]));
	if (!new_env)
		return (NULL);
	last = new_env;
	i = 1;
	while (env[i])
	{
		new_node = ft_lstnew(extract_var(env[i]), extract_value(env[i]));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&last, new_node);
		last = last->next;
		i++;
	}
	return (new_env);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*tokens;
	t_env	*new_env;

	(void)av;
	(void)ac;
	new_env = env_init(env);
	while (1337)
	{
		line = readline("minishell :");
		check_unprint(&line);
		one_space(&line);
		check_quotes(line);
		tokens = tokeniser(line);
		print_token(tokens);
		free_tokens(tokens);
		free(line);
	}
	return (0);
}
