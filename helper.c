/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:04:31 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/15 17:24:34 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	printf("malloc Error !\n");
	exit(EXIT_FAILURE);	
}

void	add_token(t_token **tokens, t_token **last, t_token_type type, const char *value)
{
	t_token	*new_token;
	
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		malloc_error();
	new_token->type = type;
    new_token->value = ft_strdup(value);
	new_token->next = NULL;
	if (!*tokens)
	{
		*tokens = new_token;
		*last = new_token;
	}
	else
	{
		(*last)->next = new_token;
		*last = new_token;
	}
}	
