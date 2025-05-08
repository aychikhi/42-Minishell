/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:55:57 by ayaarab           #+#    #+#             */
/*   Updated: 2025/05/08 15:31:53 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		path = get_env_value(*env, "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
		path = get_env_value(*env, "OLDPWD");
	else
		path = args[1];
	if (!path || chdir(path) == -1)
	{
		free(oldpwd);
		perror("cd");
		return (1);
	}
	update_env_var(env, "OLDPWD", oldpwd);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	update_env_var(env, "PWD", newpwd);
	free(newpwd);
	return (0);
}
