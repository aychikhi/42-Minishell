/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:03:38 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/20 13:37:29 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_token(char c, char *input, t_tokenize_state *state)
{
	if (c == ' ')
	{
		add_token(state->tokens, state->last, TOKEN_SPACE, " ");
		(*state->i) = skip_spaces(input, state->i);
	}
	else if (c == '|')
	{
		if (!check_pipe(input, state))
			return (0);
		else if (check_pipe(input, state) == 3)
			(*state->i)++;
		add_token(state->tokens, state->last, TOKEN_PIPE, "|");
		(*state->i)++;
	}
	else if (c == '<' || c == '>')
	{
		if (!check_red(input, state))
			return (0);
		handle_redirection(input, state->i, state->tokens, state->last);
	}
	else if (c == '\'' || c == '\"')
		handle_quotes(input, state->i, state->tokens, state->last);
	else
		handle_word(input, state->i, state->tokens, state->last);
	return (1);
}

static int	process_tokens(char *input, t_tokenize_state *state)
{
	while (input[*state->i])
	{
		if (!handle_token(input[*state->i], input, state))
			return (0);
	}
	return (1);
}

static void	finalize_tokens(t_token **tokens, t_token **last)
{
	add_token(tokens, last, TOKEN_EOF, "EOF");
	if (!check_tokens(tokens))
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return ;
	}
	process_wildcards(tokens);
	check_and_join_token(&tokens);
}

int	tokeniser(char *input, t_env *env, t_command *cmd)
{
	int					i;
	t_token				*tokens;
	t_token				*last;
	t_tokenize_state	state;
	char				*new_input;

	i = 0;
	new_input = expand_env(input, env, 0);
	last = NULL;
	tokens = NULL;
	state = tokenize_state_init(&i, &tokens, &last);
	if (!new_input)
		return (0);
	if (!process_tokens(new_input, &state))
	{
		free_tokens(tokens);
		free(new_input);
		return (0);
	}
	finalize_tokens(&tokens, &last);
	init_command(&cmd, tokens, &env);
	free_tokens(tokens);
	free(new_input);
	return (1);
}
	// print_command(cmd);//n
