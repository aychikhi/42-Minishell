#include "../../includes/minishell.h"

static char	*join_paths(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**path;
	char	*path_env;
	int		i;
	char	*full;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	i = 0;
	path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		full = join_paths(path[i], cmd);
		if (access(full, X_OK) == 0)
		{
			free_2d_arr(path);
			return (full);
		}
		free(full);
		i++;
	}
	free_2d_arr(path);
	return (NULL);
}
