/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:13:29 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/23 12:46:57 by aychikhi         ###   ########.fr       */
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
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF
}					t_token_type;

typedef struct s_file
{
	char			*name;
	int				type;
	struct s_file	*next;
}					t_file;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_file			*file;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_command
{
	t_env			*env;
	t_cmd			*cmd;
	unsigned char	exit_status;
}					t_command;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

void				error_fun(void);
char				*ft_itoa(int n);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
void				malloc_error(void);
char				*add_word(char *str);
void				one_space(char **line);
char				*extract_var(char *var);
t_token				*tokeniser(char *input);
void				check_quotes(char *line);
char				*extract_env(char *input);
void				check_unprint(char **line);
int					ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*extract_value(char *value);
void				free_tokens(t_token *tokens);
int					skip_fun(char *line, int flag);
char				**ft_split(char const *s, char c);
t_env				*ft_lstnew(void *var, void *value);
void				ft_lstadd_back(t_env **lst, t_env *new);
char				*add_word_inside_quote(char c, char *str);
void				add_token(t_token **tokens, t_token **last,
						t_token_type type, const char *value);

#endif