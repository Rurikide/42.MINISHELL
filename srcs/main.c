#include "../incls/builtins.h"
#include <unistd.h>

void	ft_init_env(char **env)
{
	size_t nb;

	nb = 0;
	while (*env != NULL)
	{
		env++;
		nb++;
	}
	printf("%d\n", nb);
	get_minishell()->env = malloc((sizeof *) * nb);

	ERROR DE MALLOC
}

t_minishell	*get_minishell(void)
{
	static t_minishell minishell;

	if (minishell.init != 1)
	{
		minishell.init = 1;
		minishell.env = NULL;
	}
	return (&minishell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell *minishell;
	char *str;
	char **options;

	ft_init_env(env);
	minishell = get_minishell();
	if (argc < 2)
		return (0);
	str = argv[1];
	options = ft_split(str, ' ');
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