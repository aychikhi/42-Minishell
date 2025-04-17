#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) {
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);
        printf("You typed: %s\n", line);
        free(line);
    }
    return 0;
}
