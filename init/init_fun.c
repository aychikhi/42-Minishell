/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:46:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/28 17:19:57 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokenize_state	tokenize_state_init(int *i, t_token **tokens,
		t_token **last)
{
	t_tokenize_state	state;

	state.i = i;
	state.tokens = tokens;
	state.last = last;
	return (state);
}

t_env	*env_init(char **env)
{
	t_env	*new_env;
	t_env	*last;
	t_env	*new_node;
	int		i;

	new_env = NULL;
	last = NULL;
	if (!env || !*env)
		return (NULL);
	new_env = ft_lstnew(extract_var(env[0]), extract_value(env[0]));
	if (!new_env)
		return (NULL);
	last = new_env;
	i = 1;
	while (env[i])
	{
		new_node = ft_lstnew(extract_var(env[i]), extract_value(env[i]));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&last, new_node);
		last = last->next;
		i++;
	}
	return (new_env);
}

void	init_command(t_command **cmd, t_token *tokens, t_env **env)
{
	if (!*cmd)
	{
		*cmd = malloc(sizeof(t_command));
		if (!*cmd)
			malloc_error();
	}
	(*cmd)->env = *env;
	init_cmd(&(*cmd)->cmd, tokens);
}
