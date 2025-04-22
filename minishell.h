/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:13:29 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/22 13:09:06 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

void				error_fun(void);
void				malloc_error(void);
char				*add_word(char *str);
void				one_space(char **line);
t_token				*tokeniser(char *input);
void				check_quotes(char *line);
void				check_unprint(char **line);
int					ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
int					skip_fun(char *line, int flag);
char				**ft_split(char const *s, char c);
int					ft_isspecial(const char *str, int i);
char				*add_word_inside_quote(char c, char *str);
void	add_token(t_token **tokens, t_token **last, t_token_type type,
		const char *value);

#endif