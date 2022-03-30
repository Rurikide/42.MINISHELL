#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>



int	main(void)
{
	// readline malloc, il faut free
	
	char *str = readline("minishell> ");

	printf("%s\n", str);
	return (0);
}
