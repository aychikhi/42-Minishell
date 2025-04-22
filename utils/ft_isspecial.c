/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspecial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:25:39 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/22 13:03:32 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspecial(const char *str, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
			break ;
		i++;
		j++;
	}
	return (j);
}
