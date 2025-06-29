/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:42:47 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 10:42:52 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	process_wildcards(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	t_token	*new_tokens;
	t_token	*new_last;

	new_tokens = NULL;
	new_last = NULL;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD && has_wildcard(current->value))
			expand_wildcard(&new_tokens, &new_last, current);
		else
			add_token(&new_tokens, &new_last, current->type, current->value);
		current = next;
	}
	free_tokens(*tokens);
	*tokens = new_tokens;
}

int	has_wildcard(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
