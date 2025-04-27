/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:54:55 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/27 16:46:13 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../execution.h"

extern int	g_exit_status;

int			ft_pwd(void);
int			ft_env(char **env);
void		ft_echo(char **args);
void		ft_exit(char **args);
int			ft_cd(char **args, char **env);
void		helper_builtins(char *cmd, char **env);

#endif