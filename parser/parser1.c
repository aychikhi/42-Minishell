/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:05:51 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/29 13:08:08 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char *input, t_tokenize_state *state)
{
	int	i;
	int	l;

	l = 0;
	i = *state->i;
	while (input[i] == '|')
	{
		i++;
		l++;
		while (input[i] == ' ')
			i++;
	}
	if (l > 1)
		return (printf("syntax error near unexpected token `|'\n"), 0);
	while (input[i] == ' ')
		i++;
	if (l == 2 && input[i])
		return (3);
	else if (input[i])
		return (1);
	else
		return (printf("syntax error near unexpected token `|'\n"), 0);
	return (1);
}

static int	handle_redirection_chars(char *input, int *i, int *l)
{
	while (input[*i] == '>' || input[*i] == '<')
	{
		(*i)++;
		(*l)++;
		while (input[*i] == ' ')
		{
			(*i)++;
			if (input[*i] == '|')
				return (printf("syntax error near unexpected token `|'\n"), 0);
		}
		if (!input[*i])
			return (printf("syntax error\n"), 0);
		if (*l == 1 && input[*i - 1] == '>' && input[*i] == '|')
			return (1);
	}
	return (2);
}

int	check_red(char *input, t_tokenize_state *state)
{
	int	i;
	int	l;
	int	ret;

	l = 0;
	i = *state->i;
	if ((input[i] == '>' && input[i + 1] == '<') || (input[i] == '<' && input[i
				+ 1] == '>'))
		return (printf("syntax error\n"), 0);
	ret = handle_redirection_chars(input, &i, &l);
	if (ret != 2)
		return (ret);
	if (input[i] == '|')
		return (printf("syntax error near unexpected token `|'\n"), 0);
	if (l > 2)
		return (printf("syntax error\n"), 0);
	return (1);
}

void	check_and_join_token(t_token ***token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = **token;
	while (tmp)
	{
		if (tmp->next && tmp->type != 1 && tmp->next->type != 1
			&& tmp->next->type != 9 && tmp->type != 9 && tmp->next->type != 2
			&& tmp->type != 2 && tmp->next->type != 3 && tmp->type != 3
			&& tmp->next->type != 4 && tmp->type != 4 && tmp->next->type != 5
			&& tmp->type != 5 && tmp->next->type != 6 && tmp->type != 6)
		{
			tmp->value = ft_strjoin(tmp->value, tmp->next->value);
			tmp->type = 0;
			tmp2 = tmp->next;
			tmp->next = tmp2->next;
		}
		else
			tmp = tmp->next;
	}
}

int	check_tokens(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp->type == 1)
		return (printf("syntax error near unexpected token `|'\n"), 0);
	while (tmp)
	{
		if ((tmp->type == 5 || tmp->type == 6 || tmp->type == 3
				|| tmp->type == 4) && tmp->next->type == 9)
			return (printf("syntax error\n"), 0);
		tmp = tmp->next;
	}
	return (1);
}
