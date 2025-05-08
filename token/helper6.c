/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:33:04 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/01 19:21:02 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_redirections(t_exp_data *data)
{
	if (data->expanded[data->i] == '<' && data->expanded[data->i + 1] == '<')
	{
		data->i++;
		data->flag = 1;
		if (data->expanded[data->i + 1])
		{
			data->i++;
			while (data->expanded[data->i] == ' ')
				data->i++;
		}
		return (1);
	}
	return (0);
}

static int	handle_quote(t_exp_data *data)
{
	if (data->expanded[data->i] == '\'' && !data->in_dq)
	{
		data->in_sq = !data->in_sq;
		return (1);
	}
	else if (data->expanded[data->i] == '\"' && !data->in_sq)
	{
		data->in_dq = !data->in_dq;
		return (1);
	}
	return (0);
}

int	process_exp_char(t_exp_data *data)
{
	char	*temp;

	if (handle_redirections(data))
		return (0);
	else if (handle_quote(data))
		return (0);
	else if (data->expanded[data->i] == '$' && !data->in_sq && !data->flag)
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
