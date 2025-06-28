/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:59:17 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/28 17:39:21 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_token(t_token **tokens, t_token **last, t_token_type type,
		const char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		malloc_error();
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->before_expand = ft_strdup(value);
	new_token->expanded = 0;
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

static int	handle_dollar(char *input)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	if (ft_isalpha(input[1]) || input[1] == '_')
	{
		i++;
		while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		{
			l++;
			i++;
		}
	}
	return (l);
}

char	*handle_env_expansion(char *input, int i, t_env *env)
{
	int		l;
	char	*result;
	char	*var_name;

	if (input[i + 1] == '?')
		return (expand_exit_status(input, i));
	l = handle_dollar(input + i);
	if (l > 0)
	{
		var_name = ft_substr(input, i + 1, l);
		if (!var_name)
			return (NULL);
		result = extract_env(input, env, i, var_name);
		free(var_name);
		return (result);
	}
	return (NULL);
}
