/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:05:51 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 13:08:59 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

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
				return (ft_putstr_fd("minishell : syntax error\n", 2), 0);
		}
		if (!input[*i])
			return (ft_putstr_fd("minishell : syntax error\n", 2), 0);
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
		return (ft_putstr_fd("minishell : syntax error\n", 2), 0);
	ret = handle_redirection_chars(input, &i, &l);
	if (ret != 2)
		return (ret);
	if (input[i] == '|')
		return (ft_putstr_fd("minishell : syntax error\n", 2), 0);
	if (l > 2)
		return (ft_putstr_fd("minishell : syntax error\n", 2), 0);
	return (1);
}

static int	should_join_tokens(t_token *current, t_token *next)
{
	return (next && current->type != 1 && next->type != 1 && next->type != 9
		&& current->type != 9 && next->type != 2 && current->type != 2
		&& next->type != 3 && current->type != 3 && next->type != 4
		&& current->type != 4 && next->type != 5 && current->type != 5
		&& next->type != 6 && current->type != 6 && next->type != 10
		&& current->type != 10);
}

static void	join_two_tokens(t_token *tmp)
{
	t_token	*tmp2;
	char	*old_value;
	char	*new_value;

	old_value = tmp->value;
	new_value = ft_strjoin(tmp->value, tmp->next->value);
	tmp->value = new_value;
	free(tmp->before_expand);
	tmp->before_expand = ft_strdup(tmp->value);
	tmp->type = 0;
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	free(old_value);
	free(tmp2->value);
	free(tmp2->before_expand);
	free(tmp2);
}

void	check_and_join_token(t_token ***token)
{
	t_token	*tmp;

	tmp = **token;
	while (tmp)
	{
		if (should_join_tokens(tmp, tmp->next))
			join_two_tokens(tmp);
		else
			tmp = tmp->next;
	}
}
