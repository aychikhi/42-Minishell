/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:37:47 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/18 17:00:10 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//TODO handle the signal ctrl+C and exit

void	signal_handler(int sig)
{
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		printf("You typed: %s\n", line);
		free(line);
	}
	return (0);
}
