/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:33:04 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/27 20:38:06 by aychikhi         ###   ########.fr       */
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

void	expand_from_token(t_token **tokens, t_env *env)
{
	t_token	*tmp;
	int		flag;
	char	*expanded;

	flag = 0;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC_quoted || tmp->type == TOKEN_HEREDOC)
			flag = 1;
		else if ((tmp->type == TOKEN_DOUBLE_QUOTE || tmp->type == TOKEN_WORD)
			&& !flag)
		{
			expanded = expand_env(tmp->type, tmp->value, env, &tmp);
			if (tmp->type == TOKEN_DOUBLE_QUOTE || !expanded[0])
			{
				free(tmp->value);
				tmp->value = expanded;
			}
			else
				free(expanded);
			flag = 0;
		}
		tmp = tmp->next;
	}
}
