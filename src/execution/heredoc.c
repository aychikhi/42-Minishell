#include "../../includes/minishell.h"


void collecting_heredoc(t_cmd *cmd)
{
	t_cmd *cur;
	t_file *file;

	cur = cmd;
	while (cur)
	{
		file = cur->file;
		while (file)
		{
			if (file->type == TOKEN_HEREDOC)
			{
				int fd = handle_heredoc(file);
				if (fd < 0)
					ft_putstr_fd("herdoc error \n", 2);
				else
					file->h_fd = fd;			
			}
			file = file->next;
		}
		cur = cur->next;
	}
}

int handle_heredoc(t_file *file)
{
	int pipe_fd[2];
	char *line;
	
	if (pipe(pipe_fd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, file->name))
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	return pipe_fd[0];
}
