/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:33:04 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 12:41:52 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	process_exp_char(t_exp_data *data)
{
	char	*temp;

	if (data->expanded[data->i] == '$')
	{
		temp = handle_env_expansion(data->expanded, data->i, data->env);
		if (temp)
		{
			free(data->expanded);
			data->expanded = temp;
			data->i = 0;
			return (1);
		}
	}
	return (0);
}

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_token_expansion(t_token *tmp, t_env *env)
{
	char	*expanded;

	expanded = expand_env(tmp->type, tmp->value, env, &tmp);
	if (is_empty(expanded) && tmp->type == TOKEN_WORD && tmp->expanded)
	{
		tmp->value[0] = '\0';
		free(expanded);
	}
	else if (tmp->type == TOKEN_DOUBLE_QUOTE || !expanded[0])
	{
		free(tmp->value);
		tmp->value = expanded;
	}
	else
		free(expanded);
}

void	expand_from_token(t_token **tokens, t_env *env)
{
	t_token	*tmp;
	int		flag;

	flag = 0;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC_quoted || tmp->type == TOKEN_HEREDOC)
			flag = 1;
		else if ((tmp->type == TOKEN_DOUBLE_QUOTE || tmp->type == TOKEN_WORD)
			&& !flag)
		{
			handle_token_expansion(tmp, env);
			flag = 0;
		}
		tmp = tmp->next;
	}
}
