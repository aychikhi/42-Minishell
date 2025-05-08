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

static void print_exported_env(t_env *env)
{
    while (env) {
        if (env->value)
            printf("declare -x %s=\"%s\"\n", env->key, env->value);
        else
            printf("declare -x %s\n", env->key);
        env = env->next;
    }
}

int ft_export(char **args, t_env **env)
{
    if (!args[1]) {
        print_exported_env(*env);
        return (0);
    }

    int status = 0;
    for (int i = 1; args[i]; i++) {
        char *eq = ft_strchr(args[i], '=');
        char *key = eq ? ft_substr(args[i], 0, eq - args[i]) : ft_strdup(args[i]);
        
        if (!is_valid_key(key)) {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            status = 1;
        }
        else if (eq)
            update_env_var(env, key, eq + 1);
        else
            update_env_var(env, key, "");
        
        free(key);
    }
    return (status);
}