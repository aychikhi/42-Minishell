/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_newfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:29:04 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/20 13:52:58 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_file	*add_newfile(void *name, int type)
{
	t_file	*tmp;

	tmp = malloc(sizeof(t_file));
	if (!tmp)
		malloc_error();
	tmp->name = name;
	tmp->type = type;
	tmp->next = NULL;
	tmp->h_fd = -1;
	tmp->quoted = 0;
	return (tmp);
}
