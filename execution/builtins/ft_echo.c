/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:05 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/18 16:56:06 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_echo(char **args)
{
	int i;
	int nl;

	i = 1;
	nl = 1;
	while(args[i] && ft_strncmp(args[i], "-n" , 2) == 0)
	{
		int j = 2;
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if(args[i][j] != '\0')
			break;
		if (args[i][j] == '\0')
			nl = 0;
		else
			break;
		
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	g_exit_status = 0; 
}