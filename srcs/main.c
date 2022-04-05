#include "../incls/builtins.h"
#include <unistd.h>

// t_singleton	*get_singleton(void)
// {
// 	static t_singleton single;

// 	if (single.init != 1)
// 	{
// 		single.init = 1;
// 		single.login1 = "adubeau";
// 		single.login2 = "tshimoda";
// 	}
// 	return (&single);
// }

int	main(int argc, char **argv, char **envp)
{
	char *str;
	char **options;
	(void)argc;
	(void)envp;

	str = argv[1];
	options = ft_split(str, ' ');

	printf("the options[0] = %s\n", options[0]);

	if (ft_is_builtin("echo", options[0]) == YES)
		builtin_echo(&options[1]);
	else if (ft_is_builtin("cd", options[0]) == YES)
		builtin_cd(&options[1]);

	ft_free_table(options);


	// while (1)
	// {
	// 	char *str = readline("minishell> ");
	// 	printf("%s\n", str);
	// 	add_history(str);
	// }

	// readline il faut free
	return (0);
}