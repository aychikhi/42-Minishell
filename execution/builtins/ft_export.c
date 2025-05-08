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

static void	print_export(t_env *env)
{
	if(!env)
		return ;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}
int check_len(char *arg)
{
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static int	process_export_arg(char *arg, t_env **env)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (!is_valid_key(arg) )
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		value = ft_strdup(eq + 1);
		update_env_var(env, key, value);
		free(key);
		free(value);
	}
	else
		update_env_var(env, arg, NULL);
	return (0);
}

int	ft_export(char **args, t_env **env)
{
    int	status = 0;
    int	i = 1;

    if (!args || !args[1])
        return (print_export(*env), 0);
    while (args[i])
        status |= process_export_arg(args[i++], env);
    return (status);
}