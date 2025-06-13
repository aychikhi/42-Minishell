/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:30:17 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/08 18:30:17 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
