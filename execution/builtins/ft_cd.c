/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:55:57 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/29 22:42:05 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(char **args, t_env **env)
{
	char	*oldpwd;
	char	*path;
	char	*newpwd;
	int		ret;

	oldpwd = get_env_value(*env, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if (!args[1] || args[1][0] == '~')
		path = get_env_value(*env, "HOME");
	else if (args[1][0] == '-')
		path = get_env_value(*env, "OLDPWD");
	else
		path = args[1];
	if (!path)
		return (ft_putstr_fd("cd: path not set\n", 2), 1);
	ret = chdir(path);
	if (ret == -1)
		return (perror("cd"), 1);
	newpwd = getcwd(NULL, 0);
	update_env_var(env, "OLDPWD", oldpwd);
	update_env_var(env, "PWD", newpwd);
	free(newpwd);
	return (0);
}
