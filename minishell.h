/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:13:29 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/12 12:36:18 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

typedef struct s_cmd
{
	void	*cmd;
	void	*next;
}			t_cmd;

int		ft_strlen(char	*str);
t_cmd	*ft_lstnew(void *cmd1);
int		ft_isspecial(char *str, int i);
char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);

#endif