/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:12:17 by ayaarab             #+#    #+#             */
/*   Updated: 2025/06/29 17:12:18 by ayaarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int useless(t_cmd *cmd , char **path)
{
	if (!path)
	{
		handle_path_not_found(cmd);
		return (0);
	}
	return (1);
}