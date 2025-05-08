/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:54:55 by ayaarab           #+#    #+#             */
/*   Updated: 2025/05/08 15:31:08 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../execution.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

extern int			g_exit_status;

int					ft_pwd(void);
int					ft_env(t_env *env);
int					ft_cd(char **args, t_env **env);
int					ft_unset(char **args, t_env **env);
int					ft_export(char **args, t_env **env);
void				ft_echo(char **args);
void				ft_exit(char **args);

//env
t_env				*env_to_list(char **env);
char				**list_to_env(t_env *list);
// int is_valid_key(char *key);
char				*get_env_value(t_env *env, const char *key);
void				update_env_var(t_env **env, const char *key,
						const char *value);
void				helper_builtins(char *cmd, t_env **env);
int					is_valid_key(char *key);

#endif