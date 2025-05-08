/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:29 by ayaarab           #+#    #+#             */
/*   Updated: 2025/05/08 15:30:53 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *first, const char *second)
{
	size_t	i;

	i = 0;
	while (first[i] != '\0' && second[i] != '\0')
	{
		if (first[i] != second[i])
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i++;
	}
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}
