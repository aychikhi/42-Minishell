/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:13:29 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/14 16:58:08 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

// typedef enum e_token
// {
// 	string,
// 	pipe,
// 	and,
// 	or,
// 	redirections,
// }			t_token;

typedef struct s_cmd
{
	void			*cmd;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_lst
{
	void	*str;
	// t_token	token;
	int		len;
}			t_lst;

void	error_fun(void);
int		ft_strlen(char	*str);
void	one_space(char **line);
t_cmd	*ft_lstnew(void *cmd1);
void	check_quotes(char *line);
void	check_unprint(char **line);
int		ft_isspecial(char *str, int i);
char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);

#endif