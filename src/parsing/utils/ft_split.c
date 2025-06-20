/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:16:39 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/20 13:27:16 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_word(const char *str, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str && str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			res++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (res);
}

static int	len(const char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != c)
	{
		j++;
		i++;
	}
	return (j);
}

void	free_2d_arr(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		l;
	int		i;
	int		j;

	i = 0;
	l = 0;
	j = 0;
	if (!s)
		return (NULL);
	ptr = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (ptr && i < count_word(s, c))
	{
		j += l;
		while (s[j] == c)
			j++;
		l = len(s, c, j);
		ptr[i] = malloc((l + 1) * sizeof(char));
		if (!ptr[i])
			return (free_2d_arr(ptr), free(ptr), NULL);
		ft_strncpy(ptr[i++], s + j, l);
	}
	return (ptr[i] = NULL, ptr);
}
