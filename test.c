#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype
void check_unprint(char **line);

int main(void)
{
    // Test cases
    char *test1 = strdup("Hello\x01World!"); // Contains ASCII 1
    char *test2 = strdup("\x02\x03Test\x04String\x05"); // Multiple unprintable characters
    char *test3 = strdup("NoUnprintablesHere"); // No unprintable characters
    char *test4 = strdup(""); // Empty string
    char *test5 = NULL; // NULL input

    // Print original strings
    printf("Original strings:\n");
    printf("Test1: %s\n", test1);
    printf("Test2: %s\n", test2);
    printf("Test3: %s\n", test3);
    printf("Test4: %s\n", test4);

    // Apply check_unprint
    check_unprint(&test1);
    check_unprint(&test2);
    check_unprint(&test3);
    check_unprint(&test4);
    check_unprint(&test5); // Should handle NULL gracefully

    // Print modified strings
    printf("\nModified strings:\n");
    printf("Test1: %s\n", test1);
    printf("Test2: %s\n", test2);
    printf("Test3: %s\n", test3);
    printf("Test4: %s\n", test4);

    // Free allocated memory
    free(test1);
    free(test2);
    free(test3);
    free(test4);

    return 0;
}

// Function implementation (copied from your code)
void	check_unprint(char **line)
{
	int i;
	int f;

    if (!line || !*line)
        return;
	i = 0;
	f = 0;
	while (line[0][f])
	{
		if (line[0][f] >= 1 && line[0][f] <= 31)
			f++;
		else
		{
			line[0][i] = line[0][f];
			f++;
			i++;
		}
	}
	line[0][i] = '\0'; 
}