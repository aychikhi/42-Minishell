/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:17:24 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/23 12:19:50 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew(void *var, void *value)
{
	t_env	*ptr;

	ptr = malloc(sizeof(t_env));
	if (!ptr)
		malloc_error();
	ptr->var = var;
	ptr->value = value;
	ptr->next = NULL;
	return (ptr);
}
