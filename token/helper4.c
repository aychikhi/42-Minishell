/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:23:07 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/26 19:53:01 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_spaces(char *input, int *i)
{
	int	l;

	l = *i;
	while (input[l] && input[l] == ' ')
		l++;
	return (l);
}

char	*add_word(char *str)
{
	int		i;
	int		l;
	char	*ptr;

	i = 0;
	l = 0;
	while (str[l] && str[l] != '\'' && str[l] != '\"' && str[l] != ' '
		&& str[l] != '<' && str[l] != '>' && str[l] != '|')
		l++;
	ptr = malloc(l + 1);
	if (!ptr)
		malloc_error();
	while (i < l)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*add_word_inside_quote(char c, char *str)
{
	int		l;
	int		i;
	char	*ptr;

	i = 0;
	l = 0;
	while (str[l] && str[l] != c)
		l++;
	ptr = malloc(l + 1);
	if (!ptr)
		malloc_error();
	while (i < l)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
