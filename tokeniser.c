/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:03:38 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/24 15:37:13 by aychikhi         ###   ########.fr       */
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
	while (str[l] && str[l] != ' ' && str[l] != '<' && str[l] != '>')
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

static void	handle_token(char c, char *input, t_tokenize_state *state)
{
	if (c == ' ')
		(*state->i)++;
	else if (c == '|')
	{
		add_token(state->tokens, state->last, TOKEN_PIPE, "|");
		(*state->i)++;
	}
	else if (c == '<' || c == '>')
		handle_redirection(input, state->i, state->tokens, state->last);
	else if (c == '\'' || c == '\"')
		handle_quotes(input, state->i, state->tokens, state->last);
	else
		handle_word(input, state->i, state->tokens, state->last);
}

t_token	*tokeniser(char *input, t_env *env)
{
	int					i;
	t_token				*tokens;
	t_token				*last;
	t_tokenize_state	state;

	i = 0;
	(void)env;
	last = NULL;
	tokens = NULL;
	state.i = &i;
	state.tokens = &tokens;
	state.last = &last;
	if (!input)
		return (NULL);
	while (input[i])
		handle_token(input[i], input, &state);
	add_token(&tokens, &last, TOKEN_EOF, "EOF");
	return (tokens);
}
