/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:13:29 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 17:18:35 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include <dirent.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

# define RESET "\e[0m"
# define PURPLE "\e[1;95m"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SPACE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_EOF,
	TOKEN_HEREDOC_quoted,
}					t_token_type;

typedef struct s_file
{
	char			*name;
	int				type;
	int				h_fd;
	int				quoted;
	struct s_file	*next;
}					t_file;

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
}					t_command;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				expanded;
	struct s_token	*next;
}					t_token;

typedef struct s_tokenize_state
{
	int				*i;
	t_token			**tokens;
	t_token			**last;
}					t_tokenize_state;

typedef struct s_exp_data
{
	int				i;
	t_env			*env;
	char			*expanded;
}					t_exp_data;

int					error_fun(void);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
void				malloc_error(void);
t_cmd				*add_new(int size);
void				print_ballas(void);
void				free_env(t_env *env);
void				free_cmd(t_cmd *cmd);
char				*add_word(char *str);
t_env				*env_init(char **env);
void				free_file(t_file *file);
char				*extract_var(char *var);
int					check_quotes(char *line);
int					arg_size(t_token *tokens);
char				*ft_strdup(const char *s1);
int					ft_strlen(const char *str);
t_token				*create_nude(char **array);
void				check_unprint(char **line);
char				*extract_value(char *value);
int					is_redirect_token(int type);
void				free_tokens(t_token *tokens);
t_token				*skip_spaces2(t_token *token);
int					skip_fun(char *line, int flag);
int					check_tokens(t_token **tokens);
int					check_wildcard(t_token *tokens);
int					skip_spaces(char *input, int *i);
char				**ft_split(char const *s, char c);
t_file				*add_newfile(void *name, int type);
t_env				*ft_lstnew(void *var, void *value);
int					check_tokens_errors(t_token *tokens);
void				init_cmd(t_cmd **cmd, t_token *tokens);
void				check_and_join_token(t_token ***token);
void				add_backfile(t_file **lst, t_file *new);
void				ft_lstadd_back(t_env **lst, t_env *new);
char				*ft_strcpy(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
char				*add_word_inside_quote(char c, char *str);
void				handle_out_redirection(char *input, int *i,
						t_token **tokens, t_token **last);
void				add_token(t_token **tokens, t_token **last,
						t_token_type type, const char *value);
int					print_ambiguous_error(void);
char				*ft_strjoin(char const *s1, char const *s2);
t_tokenize_state	tokenize_state_init(int *i, t_token **tokens,
						t_token **last);
int					process_exp_char(t_exp_data *data);
char				*ft_substr(char const *s, int start, int len);
char				*expand_env(int type, char *input, t_env *env,
						t_token **tokens);
void				expand_from_token(t_token **tokens, t_env *env);
char				*ft_strncpy(char *dest, const char *src, int n);
int					check_red(char *input, t_tokenize_state *state);
int					check_pipe(char *input, t_tokenize_state *state);
void				handle_word(char *input, int *i, t_token **tokens,
						t_token **last);
int					tokeniser(char *input, t_env *env, t_command *cmd);
void				handle_quotes(char *input, int *i, t_token **tokens,
						t_token **last);
char				*extract_env(char *input, t_env *env, int dollar_pos,
						char *var_name);
char				*handle_env_expansion(char *input, int i, t_env *env);
void				init_exp_data(t_exp_data *data, char *input, t_env *env);
void				handle_redirection(char *input, int *i, t_token **tokens,
						t_token **last);
void				handle_in_redirection(char *input, int *i, t_token **tokens,
						t_token **last);
void				init_command(t_command **cmd, t_token *tokens, t_env **env);
void				process_token(t_cmd **tmp, t_token **tokens, int *i,
						int *flag);

void				execute_pipeline(t_cmd *cmds, t_env *env);
int					execute_builtin(t_cmd *cmd, t_env **env);
void				exec_externals(t_cmd *cmd, t_env *env);
void				exec_externals_in_child(t_cmd *cmd, t_env *env);
void				handle_fork_error(char *path, char **envp);
void				handle_path_not_found(t_cmd *cmd);
void				execute_child_process(t_cmd *cmd, char *path, char **envp);
void				write_line_to_pipe(int pipe_fd, char *line, t_env *env,
						int expand);
void				handle_redir(t_file *f);
int					open_file_by_type(t_file *f);
void				handle_heredoc(t_file *f);

void				free_pipes(int **pipes, int count);
void				wait_all(pid_t *pids, int count);

void				apply_redirection(t_cmd *cmd);
int					count_cmd(t_cmd *cmd);
int					is_builtin(char *cmd);
void				set_signals_interactive(void);
void				set_signals_in_child(void);
void				set_signals_for_child_execution(void);
void				set_signals_heredoc(void);
void				update_exit_status(int status);
void				reset_heredoc_state(void);
char				*ft_itoa(int n);
char				*expand_exit_status(char *input, int i);

void				close_pipes(int **pipe, int count);
int					**create_pipes(int count);
int					collecting_heredoc(t_cmd *cmd, t_env *env);
int					ft_file_exists(char *filename);

void				help(t_cmd *cmd);
int					useless(t_cmd *cmd, char **path);

/* Wildcard expansion */
int					has_wildcard(const char *str);
void				expand_wildcard(t_token **tokens, t_token **last,
						t_token *current);
void				process_wildcards(t_token **tokens);

#endif