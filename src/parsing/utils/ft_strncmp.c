/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:40:06 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/20 13:53:44 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strncmp(char *first, char *second, size_t length)
{
	size_t	i;

	i = 0;
	if (length == 0)
		return (0);
	while (i < length && (first[i] != '\0' || second[i] != '\0'))
	{
		if ((unsigned char)first[i] != (unsigned char)second[i])
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i++;
	}
	return (0);
}
