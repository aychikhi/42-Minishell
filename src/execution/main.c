/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:47 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/27 16:29:24 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int g_exit_status;

static void handle_sigint(int sig) 
{
    if (sig == SIGINT) 
    {
        write(1, "\n", 1);
        g_exit_status = 130;
    }
    else if (sig == SIGQUIT)
    {
        write(1, "Quit: 3\n", 8);
        g_exit_status = 131;
    }
}

int main(int argc, char **argv, char **env) {
    char *line;
    t_env *env_list;
    t_command *cmd = NULL;

    (void)argc;
    (void)argv;
    g_exit_status = 0;
    env_list = env_to_list(env);
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigint);
    while (1) 
    {
        line = readline("minishell$ ");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (*line) 
        {
            add_history(line);
            tokeniser(line, env_list, cmd);
            execute_builtin(cmd, &env_list);
        }
        free(line);
    }
    clear_history();
    return (g_exit_status);
}
