/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:19:00 by aychikhi          #+#    #+#             */
/*   Updated: 2025/06/29 17:19:09 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	useless(t_cmd *cmd, char **path)
{
	if (!path)
	{
		handle_path_not_found(cmd);
		return (0);
	}
	return (1);
}
