/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:55:55 by ayaarab           #+#    #+#             */
/*   Updated: 2025/04/18 16:58:05 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_pwd(void)
{
    char *path = getcwd(NULL, 0);
    if (!path)
    {
        perror("minishell: pwd");
        return (1);
    }
    printf("%s\n", path);
    free(path);
    return (0);
}
