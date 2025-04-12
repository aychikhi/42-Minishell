/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/12 13:01:11 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av) {
    char *input;
    int i = 1;

    // Ensure there are enough arguments
    if (ac < 2) {
        fprintf(stderr, "Usage: %s <prompts...>\n", av[0]);
        return 1;
    }

    while (i < ac) {
        // Prompt the user with av[i] and read input
        input = readline(av[i]);

        // Check for EOF or empty input
        if (!input || *input == '\0') {
            free(input);
            break;
        }

        // Process the input (example: print it)
        printf("You entered: %s\n", input);

        // Free the allocated memory
        free(input);

        // Move to the next prompt
        i++;
    }

    return 0;
}
// int main(int ac, char **av)
// {
// 	// (void)av;
// 	int		i;
// 	int		j;
// 	char	*line;
// 	char	*cmd;
// 	t_cmd	*lst;

// 	lst = NULL;
// 	if (ac > 1)
// 	{
// 		// printf("hh\n");
// 		i = 1;
// 		while (i < ac)
// 		{	
// 			line = readline(av[i]);
// 			i++;
// 		}
// 		// printf("-------w%sw-------\n", line);
// 		i = 0;
// 		j = 0;
// 		while (1)
// 		{ 
// 			// printf("hhhh\n");
// 			j = ft_isspecial(line, j);
// 			cmd = malloc ((j - i) + 1);
// 			int k = 0;
// 			while (i < j)
// 			{
// 				cmd[k] = line[j];
// 				i++;
// 				k++;
// 			}
// 			cmd[k] = '\0';
// 			if (!lst)
// 				lst = ft_lstnew(cmd);
// 			else
// 				ft_lstadd_back(&lst, ft_lstnew(cmd));
// 			// printf("hh%s\n", cmd);
// 			free (cmd);
// 			if (j == ft_strlen(line))
// 				break;
// 			i = j;
// 		}
// 		// while (lst)
// 		// {
// 		// 	printf("---->%s<----\n", lst->cmd);
// 		// 	lst = lst->next;
// 		// }
// 		// printf("hh1\n");
// 	}
// 	return (0);
// }
