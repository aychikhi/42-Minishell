/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:55:57 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/27 17:24:05 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_env_value(const char *name, char **env)
{
	int		i;
	char	*value;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
		{
			value = ft_strdup(env[i] + ft_strlen(name) + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	ft_cd(char **args, char **env)
{
	char	*path;
	int		ret;

	if (args[1] == NULL)
	{
		path = get_env_value("HOME", env);
		if (path == NULL)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	else
		path = args[1];
	ret = chdir(path);
	if (ret == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
