#include "../../includes/minishell.h"

char *expand_exit_status(char *input, int i)
{
    char    *exit_str;
    char    *new_input;
    int     new_len;

    exit_str = ft_itoa(g_exit_status);
    new_len = ft_strlen(input) - 2 + ft_strlen(exit_str) + 1;
    new_input = malloc(new_len);
    if (!new_input)
        malloc_error();
    ft_strncpy(new_input, input, i);
    new_input[i] = '\0';
    ft_strcpy(new_input + i, exit_str);
    ft_strcpy(new_input + i + ft_strlen(exit_str), input + i + 2);
    free(exit_str);
    return (new_input);
}
