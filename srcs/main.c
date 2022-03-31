#include "../incls/builtins.h"

int	main(void)
{
	// readline malloc, il faut free
	
	char *str = readline("minishell> ");

	printf("%s\n", str);
	return (0);
}


// int	main(int argc, char **argv)
// {
// 	char *str;

// 	if (argc == 2)
// 	{
// 		str = argv[1];
// 		ft_echo(str, 0);
// 	}
// 	return (0);
// }