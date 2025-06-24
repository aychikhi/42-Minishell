/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:33:04 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/24 17:12:41 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	process_exp_char(t_exp_data *data, int flag)
{
	char	*temp;

	if (data->expanded[data->i] == '$' && !flag)
	{
		temp = handle_env_expansion(data->expanded, data->i, data->env);
		if (temp)
		{
			free(data->expanded);
			data->expanded = temp;
			data->i = 0;
			if (data->in_dq)
				data->in_dq = !data->in_dq;
			return (1);
		}
	}
	return (0);
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
		else if ((tmp->type == TOKEN_DOUBLE_QUOTE || tmp->type == TOKEN_WORD))
		{
			tmp->value = expand_env(tmp->value, env, flag);
			flag = 0;
		}
		tmp = tmp->next;
	}
}
