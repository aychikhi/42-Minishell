#include "../../includes/minishell.h"

static void handle_heredoc_child(int pipe_fd[2], char *delimiter)
{
    char *line;
    
    set_signals_heredoc();
    close(pipe_fd[0]);
    
    while (1)
    {
        line = readline("> ");
        if (!line || !ft_strcmp(line, delimiter))
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    exit(EXIT_SUCCESS);
}

static void handle_heredoc_parent(int pipe_fd[2], t_file *file, pid_t pid)
{
    int status;
    
    close(pipe_fd[1]);
    waitpid(pid, &status, 0);
	if(WIFSIGNALED(status))
	{
		close(pipe_fd[0]);
		g_exit_status = 130;
	}
	file->h_fd = pipe_fd[0];
}

static int setup_heredoc_pipe(int pipe_fd[2])
{
    if (pipe(pipe_fd) < 0)
    {
        ft_putstr_fd("minishell: pipe error\n", 2);
        return (0);
    }
    return (1);
}

static void process_heredoc(t_file *file)
{
    int pipe_fd[2];
    pid_t pid;
    
    if (!setup_heredoc_pipe(pipe_fd))
        return;
    
    pid = fork();
    if (pid == 0)
        handle_heredoc_child(pipe_fd, file->name);
    else
        handle_heredoc_parent(pipe_fd, file, pid);
}

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
                process_heredoc(file);
            file = file->next;
        }
        cur = cur->next;
    }
}
