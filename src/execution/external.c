# include "../../includes/minishell.h"

static char *join_paths(char *dir , char *cmd)
{
	char *tmp;
	char *path;

	tmp = ft_strjoin(dir , "/");
	path = ft_strjoin(tmp , cmd);

	free(tmp);
	return path;
}

char *get_cmd_path(char *cmd ,t_env *env)
{
	char **path;
	char *path_env;
	int i;
	char *full;

	path_env = get_env_value(env ,"PATH");
	if (!path_env || !cmd)
		return NULL;
	i = 0;
	path = ft_split(path_env , ':');
	while (path[i])
	{
		full = join_paths(path[i],cmd);
		if (access(full , X_OK))
		{
			free_2d_arr(path);
			return full;
		}
		free(full);
		i++;
	}
	free_2d_arr(path);
	return (NULL);
}

void	exec_externals(t_cmd *cmd ,t_env *env)
{
	pid_t pid;
	char *path;
	char **envp;

	path = get_cmd_path(cmd->cmd , env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found", 2);
		ft_putstr_fd(cmd->cmd , 2);
		ft_putstr_fd("\n" , 2);
		g_exit_status = 127;
		return ;
	}
	envp = list_to_env(env);
	pid = fork();
	if (pid == 0)
	{
		execve(path , cmd->args ,envp);
		perror("execve");
		exit(1);
	}
	else
		waitpid(pid ,&g_exit_status , 0);
	free(path);
	free_2d_arr(envp);	
}
