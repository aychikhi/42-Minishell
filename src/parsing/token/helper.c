/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:04:31 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 11:12:19 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_token	*lstlast(t_token *lst)
{
	t_token	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

static int	free_split_array(char **array)
{
	int	j;

	j = 0;
	while (array[j])
	{
		free(array[j]);
		j++;
	}
	free(array);
	return (j);
}

static void	connect_tokens(t_token *tmp, t_token *new_list)
{
	t_token	*save_next2;
	t_token	*save_next;
	t_token	*save_last;

	if (new_list->next)
	{
		save_next2 = tmp->next;
		save_next = new_list->next;
		new_list->next = NULL;
		tmp->next = save_next;
		save_last = lstlast(save_next);
		if (save_last)
			save_last->next = save_next2;
	}
}

static int	handle_word_expansion(t_exp_data *data, t_token *tmp)
{
	char	**new_expanded;
	t_token	*new_list;
	int		i;

	i = 0;
	new_expanded = ft_split(data->expanded, ' ');
	if (!new_expanded)
		return (0);
	new_list = create_nude(new_expanded);
	i = free_split_array(new_expanded);
	if (i > 1)
		tmp->flag = 1;
	if (!new_list)
		return (0);
	free(tmp->value);
	tmp->value = ft_strdup(new_list->value);
	connect_tokens(tmp, new_list);
	free(new_list->value);
	free(new_list);
	return (1);
}

char	*expand_env(int type, char *input, t_env *env, t_token **tokens)
{
	t_exp_data	data;
	t_token		*tmp;

	tmp = *tokens;
	init_exp_data(&data, input, env);
	while (data.expanded && data.i >= 0 && data.expanded[data.i])
	{
		if (process_exp_char(&data))
		{
			if (type == TOKEN_WORD)
			{
				tmp->expanded = 1;
				if (handle_word_expansion(&data, tmp))
					break ;
			}
		}
		data.i++;
		if (data.i > (int)ft_strlen(data.expanded))
			break ;
	}
	return (data.expanded);
}
