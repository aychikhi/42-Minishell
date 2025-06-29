/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:22:51 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 10:34:10 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	ft_cmp(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

int	is_redirect_token(int type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND);
}

static int	check_wildcard_condition(t_token *token, int flag)
{
	if (flag && token->type == TOKEN_WORD && ft_cmp(token->value))
		return (print_ambiguous_error(token->before_expand));
	return (1);
}

int	check_wildcard(t_token *tokens)
{
	t_token	*tmp;
	int		flag;
	int		result;

	tmp = tokens;
	while (tmp)
	{
		flag = 0;
		if (is_redirect_token(tmp->type))
		{
			flag = 1;
			tmp = tmp->next;
			tmp = skip_spaces2(tmp);
		}
		if (tmp)
		{
			result = check_wildcard_condition(tmp, flag);
			if (!result)
				return (result);
			tmp = tmp->next;
		}
	}
	return (1);
}
