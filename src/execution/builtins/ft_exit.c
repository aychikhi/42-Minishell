/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:10 by ayaarab           #+#    #+#             */
/*   Updated: 2025/05/08 15:32:33 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_num(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	handel_args(char **args)
{
	int	exit_code;

	if (!is_num(args[1]))
	{
		ft_putstr_fd("minishell: exit: %s: numeric argument required\n", 2);
		exit(2);
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return (-1);
	}
	exit_code = ft_atoi(args[1]);
	exit_code %= 256;
	return (exit_code);
}

void	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (args[1])
	{
		exit_code = handel_args(args);
		if (exit_code == -1)
			return ;
	}
	else
		exit_code = g_exit_status;
	clear_history();
	exit(exit_code);
}
