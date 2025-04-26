/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:10 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/18 16:56:11 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int  is_num(const char *str)
{
	int  i = 0;
	
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if(!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void ft_exit(char **args)
{
	int exit_code = 0;

	printf("exit\n");
	if(args[1]) // exit 42
	{
		if(!is_num(args[1])) // exit tbe
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[1]);
			exit(2);
		}
		else if (args[2]) //exit 13 37
		{
			fprintf(stderr, "minishell: exit: too many arguments\n");
			g_exit_status = 1;
			return ;
		}
		else
        {
            exit_code = ft_atoi(args[1]);
            exit_code %= 256;
        }
    }
    else
    {
        exit_code = g_exit_status;
    }
	rl_clear_history();
    exit(exit_code);
}
