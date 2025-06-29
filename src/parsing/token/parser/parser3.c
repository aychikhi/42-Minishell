/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:47:16 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 14:54:24 by aychikhi         ###   ########.fr       */
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
	if (token->next && (token->next->type == TOKEN_DOUBLE_QUOTE
			|| token->next->type == TOKEN_SINGLE_QUOTE) && flag)
		return (1);
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

int	check_tokens(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp->type == 1)
		return (ft_putstr_fd("minishell : syntax error\n", 2), 0);
	while (tmp)
	{
		if ((tmp->type == 5 || tmp->type == 6 || tmp->type == 3
				|| tmp->type == 4) && tmp->next->type == 9)
			return (ft_putstr_fd("minishell : syntax error\n", 2), 0);
		tmp = tmp->next;
	}
	return (1);
}
