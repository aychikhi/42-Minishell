/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:47:16 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/28 18:49:54 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_token	*skip_spaces2(t_token *token)
{
	while (token && token->type == TOKEN_SPACE)
		token = token->next;
	return (token);
}

int	print_ambiguous_error(char *before_expand)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(before_expand, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	return (g_exit_status = 1, 0);
}

static int	check_empty_expansion_condition(t_token *token, int flag)
{
	if (flag && token->expanded && token->value[0] == '\0')
		return (print_ambiguous_error(token->before_expand));
	return (1);
}

int	check_tokens_errors(t_token *tokens)
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
			result = check_empty_expansion_condition(tmp, flag);
			if (!result)
				return (result);
			tmp = tmp->next;
		}
	}
	return (1);
}
