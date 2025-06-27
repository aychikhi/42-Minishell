/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:02:09 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/27 11:13:27 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_token	*lstcreate(void *value)
{
	t_token	*ptr;

	ptr = malloc(sizeof(t_token));
	if (!ptr)
		malloc_error();
	ptr->value = value;
	ptr->type = TOKEN_WORD;
	ptr->next = NULL;
	return (ptr);
}

static t_token	*lstcreate_space(void *value)
{
	t_token	*ptr;

	ptr = malloc(sizeof(t_token));
	if (!ptr)
		malloc_error();
	ptr->value = value;
	ptr->type = TOKEN_SPACE;
	ptr->next = NULL;
	return (ptr);
}

static void	add_word_token(t_token **head, t_token **current, char *word)
{
	t_token	*word_token;

	word_token = lstcreate(ft_strdup(word));
	if (!*head)
	{
		*head = word_token;
		*current = word_token;
	}
	else
	{
		(*current)->next = word_token;
		*current = word_token;
	}
}

static void	add_space_token(t_token **current)
{
	t_token	*space_token;

	space_token = lstcreate_space(ft_strdup(" "));
	(*current)->next = space_token;
	*current = space_token;
}

t_token	*create_nude(char **array)
{
	t_token	*head;
	t_token	*current;
	int		i;

	if (!array || !array[0])
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (array[i])
	{
		add_word_token(&head, &current, array[i]);
		if (array[i + 1])
			add_space_token(&current);
		i++;
	}
	return (head);
}
