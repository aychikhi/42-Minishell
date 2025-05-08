/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:03 by ayaarab           #+#    #+#             */
/*   Updated: 2025/05/08 15:31:58 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*env_to_list(char **env)
{
	t_env	*head;
	t_env	*node;
	char	*equal;

	head = NULL;
	while (*env)
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (NULL);
		equal = ft_strchr(*env, '=');
		node->key = ft_substr(*env, 0, equal - *env);
		node->value = ft_strdup(equal + 1);
		node->next = head;
		head = node;
		env++;
	}
	return (head);
}

char	**list_to_env(t_env *list)
{
	char	**env;
	char	*entry;
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = list;
	while (tmp && ++count)
		tmp = tmp->next;
	env = malloc((count + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	count = 0;
	while (list)
	{
		entry = ft_strjoin(list->key, "=");
		env[count++] = ft_strjoin(entry, list->value);
		free(entry);
		list = list->next;
	}
	env[count] = NULL;
	return (env);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
}

int	ft_env(t_env *env)
{
	if (!env)
	{
		ft_putstr_fd("env: environment is empty\n", 2);
		return (1);
	}
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
