/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fun1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:34:34 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/17 17:29:00 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	arg_size(t_token *tokens)
{
	t_token	*tmp;
	int		size;

	size = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 9)
			break ;
		else if (tmp->type == 3 || tmp->type == 4 || tmp->type == 5
			|| tmp->type == 6)
			tmp = tmp->next->next->next;
		else if (tmp->type == 2)
			tmp = tmp->next;
		else
		{
			size++;
			tmp = tmp->next;
		}
	}
	return (size);
}

static void	add_file_to_cmd(t_cmd *tmp, t_token **tokens, int type, int *flag)
{
	t_file	*new_file;
	int		is_quoted;

	if ((*tokens)->next->type == 1)
		*tokens = (*tokens)->next;
	while ((*tokens)->next->type == 2)
		*tokens = (*tokens)->next;
	if ((*tokens)->next && (*tokens)->next->type != 9)
	{
		is_quoted = ((*tokens)->next->type == TOKEN_SINGLE_QUOTE
				|| (*tokens)->next->type == TOKEN_DOUBLE_QUOTE);
		new_file = add_newfile(ft_strdup((*tokens)->next->value), type);
		if (type == TOKEN_HEREDOC)
			new_file->quoted = is_quoted;
		if (!(*flag))
		{
			*flag = 1;
			tmp->file = new_file;
		}
		else
			add_backfile(&tmp->file, new_file);
		*tokens = (*tokens)->next->next;
	}
	else
		*tokens = (*tokens)->next;
}

static void	add_arg_to_cmd(t_cmd *tmp, t_token **tokens, int *i)
{
	if (!tmp->cmd)
	{
		tmp->cmd = ft_strdup((*tokens)->value);
	}
	if ((*tokens)->type != 2 && (*tokens)->type != 9)
	{
		tmp->args[*i] = ft_strdup((*tokens)->value);
		(*i)++;
	}
	*tokens = (*tokens)->next;
}

static void	handle_pipe(t_cmd **tmp, t_token **tokens, int *i, int *flag)
{
	*flag = 0;
	*i = 0;
	*tokens = (*tokens)->next;
	while ((*tokens)->type == 2)
		*tokens = (*tokens)->next;
	(*tmp)->next = add_new(arg_size(*tokens));
	*tmp = (*tmp)->next;
}

void	init_cmd(t_cmd **cmd, t_token *tokens)
{
	t_cmd	*tmp;
	int		i;
	int		flag;
	int		type;

	flag = 0;
	i = 0;
	type = 0;
	*cmd = add_new(arg_size(tokens));
	tmp = *cmd;
	while (tokens && tokens->type != 9)
	{
		if (tokens->type == 2)
			tokens = tokens->next;
		else if (tokens->type == 1)
			handle_pipe(&tmp, &tokens, &i, &flag);
		else if (tokens->type == 3 || tokens->type == 4 || tokens->type == 5
			|| tokens->type == 6)
		{
			type = tokens->type;
			add_file_to_cmd(tmp, &tokens, type, &flag);
		}
		else
			add_arg_to_cmd(tmp, &tokens, &i);
	}
}
