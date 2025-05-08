/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:15 by ayaarab           #+#    #+#             */
/*   Updated: 2025/05/08 15:34:59 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_key(char *key)
{
	
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

static void	remove_env_var(t_env **env, char *key)
{
	t_env	*prev = NULL;
	t_env	*curr = *env;

	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int	status = 0;
	int	i = 1;

	if (!args[1])
		return (0);
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			remove_env_var(env, args[i]);
		i++;
	}
	return (status);
}
