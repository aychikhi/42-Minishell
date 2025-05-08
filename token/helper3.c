/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:11:41 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/25 15:33:29 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*create_expanded_str(char *input, char *env_value, int dollar_pos,
		int var_len)
{
	int		value_len;
	char	*new_input;

	value_len = 0;
	if (env_value)
		value_len = ft_strlen(env_value);
	new_input = malloc(ft_strlen(input) - (var_len + 1) + value_len + 1);
	if (!new_input)
		malloc_error();
	ft_strncpy(new_input, input, dollar_pos);
	new_input[dollar_pos] = '\0';
	if (env_value)
		ft_strcpy(new_input + dollar_pos, env_value);
	ft_strcpy(new_input + dollar_pos + value_len, input + dollar_pos + var_len
		+ 1);
	return (new_input);
}

char	*extract_env(char *input, t_env *env, int dollar_pos, char *var_name)
{
	t_env	*tmp;
	char	*env_value;
	int		var_len;

	tmp = env;
	var_len = ft_strlen(var_name);
	env_value = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var_name))
		{
			env_value = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (create_expanded_str(input, env_value, dollar_pos, var_len));
}
