/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:54:55 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/27 15:57:34 by ayaarab          ###   ########.fr       */
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
void		helper_builtins(char *cmd, char **env);
#endif