/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:04:31 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/23 17:36:50 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	printf("malloc Error !\n");
	exit(EXIT_FAILURE);
}

void	add_token(t_token **tokens, t_token **last, t_token_type type,
		const char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		malloc_error();
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	if (!*tokens)
	{
		*tokens = new_token;
		*last = new_token;
	}
	else
	{
		(*last)->next = new_token;
		*last = new_token;
	}
}

char	*expand_env(char *input)
{
	char	*env_name;
	char	*env_value;
	int		i;

	i = 0;
	while (input[i])
	{
		// if (input[i] == '$' && input[i + 1] == '?')
		// {
		// 	env_value = ft_itoa(exit_status);
		// }
		// else
		if (input[i] == '$' && ((ft_isalpha(input[i + 1]) || input[i
					+ 1] == '_')))
		{
		}
	}
}

char	*extract_env(char *input)
{
	int		i;
	int		l;
	char	*name;

	i = 0;
	l = 0;
	while (input[l] && (ft_isalnum(input[l]) || input[l] == '_'))
		l++;
	name = malloc(l + 1);
	if (!name)
		malloc_error();
	while (i < l)
	{
		name[i] = input[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}
