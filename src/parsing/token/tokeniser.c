/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:43:26 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 17:02:30 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_token(char c, char *input, t_tokenize_state *state)
{
	if (c == ' ' || c == '\t')
	{
		add_token(state->tokens, state->last, TOKEN_SPACE, " ");
		(*state->i) = skip_spaces(input, state->i);
	}
	else if (c == '|')
	{
		if (!check_pipe(input, state))
			return (g_exit_status = 258, 0);
		else if (check_pipe(input, state) == 3)
			(*state->i)++;
		add_token(state->tokens, state->last, TOKEN_PIPE, "|");
		(*state->i)++;
	}
	else if (c == '<' || c == '>')
	{
		if (!check_red(input, state))
			return (g_exit_status = 258, 0);
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
// void	print_tokens(t_token *head)
// {
// 	t_token	*current;

// 	current = head;
// 	if (!current)
// 	{
// 		printf("No tokens to print.\n");
// 		return ;
// 	}
// 	while (current)
// 	{
// 		printf("Token Type: %d\n", current->type);
// 		printf("Token expanded: %d\n", current->expanded);
// 		printf("Token Value: %s\n", current->value ? current->value : "(null)");
// 		printf("--------------------\n");
// 		current = current->next;
// 	}
// }
// void	print_cmd(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	int			i;

// 	i = 0;
// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		i = 0;
// 		printf("cmd : [%s]\n", tmp->cmd);
// 		printf("args : ");
// 		while (tmp->args[i])
// 		{
// 			printf("[%s] ", tmp->args[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		if (tmp->file)
// 		{
// 			while (tmp->file)
// 			{
// 				printf("file : %s type : %d\n", tmp->file->name,
// 					tmp->file->type);
// 				tmp->file = tmp->file->next;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }

static int	finalize_tokens(t_token **tokens, t_token **last, t_env *env)
{
	add_token(tokens, last, TOKEN_EOF, "EOF");
	// if (!check_tokens(tokens))
	// {
	// 	free_tokens(*tokens);
	// 	*tokens = NULL;
	// 	g_exit_status = 258;
	// 	return (0);
	// }
	expand_from_token(tokens, env);
	if (!check_tokens_errors(*tokens))
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (0);
	}
	check_and_join_token(&tokens);
	if (!check_wildcard(*tokens))
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (0);
	}
	process_wildcards(tokens);
	return (1);
}

int	tokeniser(char *input, t_env *env, t_command *cmd)
{
	int					i;
	t_token				*tokens;
	t_token				*last;
	t_tokenize_state	state;

	i = 0;
	last = NULL;
	tokens = NULL;
	state = tokenize_state_init(&i, &tokens, &last);
	if (!process_tokens(input, &state))
		return (free_tokens(tokens), 0);
	if (!finalize_tokens(&tokens, &last, env))
		return (free_tokens(tokens), 0);
	init_command(&cmd, tokens, &env);
	free_tokens(tokens);
	return (1);
}
