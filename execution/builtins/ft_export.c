/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:13 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/18 16:56:14 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_key(const char *key)
{
	int  i = 0;
	if(!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return 1;
}
int			ft_export(char **args, t_env **env)
{
	int i;
	
	i = 0;
	
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (!is_valid_key(args[i]))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (1);
			}
			else
			{
				char *key = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
				char *value = ft_strdup(ft_strchr(args[i], '=') + 1);
				update_env_var(env, key, value);
				free(key);
				free(value);
			}
		}
		else
			update_env_var(env, args[i], NULL);
		i++;
	}
	if (i == 0)
	{
		t_env *tmp = *env;
		while (tmp)
		{
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else
				printf("declare -x %s\n", tmp->key);
			tmp = tmp->next;
		}
	}
	return (0);
}
