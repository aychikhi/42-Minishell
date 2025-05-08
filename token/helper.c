/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:04:31 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/01 19:20:55 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	init_exp_data(t_exp_data *data, char *input, t_env *env)
{
	data->i = 0;
	data->in_sq = 0;
	data->in_dq = 0;
	data->env = env;
	data->flag = 0;
	data->expanded = ft_strdup(input);
}

char	*expand_env(char *input, t_env *env)
{
	t_exp_data	data;

	if (!input)
		return (NULL);
	init_exp_data(&data, input, env);
	if (!data.expanded)
		return (NULL);
	while (data.expanded[data.i])
	{
		if (process_exp_char(&data))
			continue ;
		data.i++;
	}
	return (data.expanded);
}
