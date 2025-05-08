/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_backfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:33:51 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/29 14:35:12 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_file	*ft_lstlast(t_file *lst)
{
	t_file	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

void	add_backfile(t_file **lst, t_file *new)
{
	t_file	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
