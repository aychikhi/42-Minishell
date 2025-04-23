/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:03:38 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/23 13:55:04 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_word(char *str)
{
	int		i;
	int		l;
	char	*ptr;

	i = 0;
	l = 0;
	while (str[l] && str[l] != ' ' && str[l] != '<' && str[l] != '>'
		&& str[l] != '(' && str[l] != ')')
		l++;
	ptr = malloc(l + 1);
	if (!ptr)
		malloc_error();
	while (i < l)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*add_word_inside_quote(char c, char *str)
{
	int		l;
	int		i;
	char	*ptr;

	i = 0;
	l = 0;
	while (str[l] && str[l] != c)
		l++;
	ptr = malloc(l + 1);
	if (!ptr)
		malloc_error();
	while (i < l)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

t_token	*tokeniser(char *input)
{
	int		i;
	int		flag;
	char	*word;
	t_token	*tokens;
	t_token	*last;

	i = 0;
	flag = 0;
	last = NULL;
	tokens = NULL;
	if (!input)
		return (NULL);
	input = expand_env(input);/
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '|' && !flag)
		{
			add_token(&tokens, &last, TOKEN_PIPE, "|");
			i++;
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_token(&tokens, &last, TOKEN_HEREDOC, "<<");
				i += 2;
			}
			else
			{
				add_token(&tokens, &last, TOKEN_REDIR_IN, "<");
				i++;
			}
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&tokens, &last, TOKEN_APPEND, ">>");
				i += 2;
			}
			else
			{
				add_token(&tokens, &last, TOKEN_REDIR_OUT, ">");
				i++;
			}
		}
		else if (input[i] == '\'' && !flag)
		{
			word = add_word_inside_quote(input[i], input + (i + 1));
			add_token(&tokens, &last, TOKEN_SINGLE_QUOTE, word);
			i += ft_strlen(word) + 2;
			free(word);
		}
		else if (input[i] == '\"')
		{
			flag = !flag;
			word = add_word_inside_quote(input[i], input + (i + 1));
			add_token(&tokens, &last, TOKEN_WORD, word);
			i += ft_strlen(word) + 2;
			free(word);
		}
		else
		{
			word = add_word(input + i);
			add_token(&tokens, &last, TOKEN_WORD, word);
			i += ft_strlen(word);
			free(word);
		}
	}
	add_token(&tokens, &last, TOKEN_EOF, "EOF");
	return (tokens);
}
