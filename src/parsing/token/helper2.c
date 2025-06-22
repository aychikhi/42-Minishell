/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:24:22 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/22 16:02:13 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_expand(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	handle_in_redirection(char *input, int *i, t_token **tokens,
		t_token **last)
{
	if (input[*i + 1] == '<')
	{
		if (check_expand(input, *i + 2))
		{
			add_token(tokens, last, TOKEN_HEREDOC_quoted, "<<");
			*i += 2;
			return ;
		}
		add_token(tokens, last, TOKEN_HEREDOC, "<<");
		*i += 2;
	}
	else
	{
		add_token(tokens, last, TOKEN_REDIR_IN, "<");
		(*i)++;
	}
}

void	handle_out_redirection(char *input, int *i, t_token **tokens,
		t_token **last)
{
	if (input[*i + 1] == '>')
	{
		add_token(tokens, last, TOKEN_APPEND, ">>");
		*i += 2;
	}
	else
	{
		add_token(tokens, last, TOKEN_REDIR_OUT, ">");
		(*i)++;
	}
}

void	handle_redirection(char *input, int *i, t_token **tokens,
		t_token **last)
{
	if (input[*i] == '<')
		handle_in_redirection(input, i, tokens, last);
	else if (input[*i] == '>')
		handle_out_redirection(input, i, tokens, last);
}

void	handle_quotes(char *input, int *i, t_token **tokens, t_token **last)
{
	char	*word;

	if (input[*i] == '\'')
	{
		word = add_word_inside_quote(input[*i], input + (*i + 1));
		add_token(tokens, last, TOKEN_SINGLE_QUOTE, word);
		*i += ft_strlen(word) + 2;
		free(word);
	}
	else if (input[*i] == '\"')
	{
		word = add_word_inside_quote(input[*i], input + (*i + 1));
		add_token(tokens, last, TOKEN_DOUBLE_QUOTE, word);
		*i += ft_strlen(word) + 2;
		free(word);
	}
}
