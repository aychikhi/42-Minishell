/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:06:17 by ayaarab           #+#    #+#             */
/*   Updated: 2025/06/13 17:08:52 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_wildcard(const char *str)
{
	int	i;
	int	in_quotes;

	if (!str)
		return (0);
	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quotes = !in_quotes;
		if (str[i] == '*' && !in_quotes)
			return (1);
		i++;
	}
	return (0);
}

static int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')
		return (0);
	if (*pattern == '*')
		return (match_pattern(pattern + 1, str) || match_pattern(pattern, str
				+ 1));
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

static void	sort_matches(char **matches, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(matches[i], matches[j]) > 0)
			{
				temp = matches[i];
				matches[i] = matches[j];
				matches[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	expand_wildcard(t_token **tokens, t_token **last, t_token *current)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;
	int				max_matches;

	dir = opendir(".");
	if (!dir)
		return ;
	max_matches = 100;
	matches = (char **)malloc(sizeof(char *) * max_matches);
	if (!matches)
	{
		closedir(dir);
		return ;
	}
	count = 0;
	while ((entry = readdir(dir)) != NULL && count < max_matches)
	{
		if (entry->d_name[0] != '.' || current->value[0] == '.')
		{
			if (match_pattern(current->value, entry->d_name))
				matches[count++] = ft_strdup(entry->d_name);
		}
	}
	closedir(dir);
	if (count > 0)
	{
		sort_matches(matches, count);
		// Add the first match
		add_token(tokens, last, TOKEN_WORD, matches[0]);
		free(matches[0]);
		// For remaining matches, add a space token followed by the word token
		for (int i = 1; i < count; i++)
		{
			add_token(tokens, last, TOKEN_SPACE, " ");
			add_token(tokens, last, TOKEN_WORD, matches[i]);
			free(matches[i]);
		}
	}
	else
		add_token(tokens, last, TOKEN_WORD, current->value);
	free(matches);
}
