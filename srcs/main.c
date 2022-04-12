
#include "builtins.h"

t_minishell	*get_minishell(void)
{
	static t_minishell minishell;

	if (minishell.init != 1)
	{
		minishell.init = 1;
		minishell.shlvl = 2;
		minishell.env = NULL;
		minishell.env_size = 0;
	}
	return (&minishell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell *minishell;
	char *str;
	char **options;

	init_env(env);
	minishell = get_minishell();
	if (argc < 2)
		return (0);
	str = argv[1];
	options = ft_split(str, ' ');
	if (ft_is_a_match("echo", options[0]) == YES)
		builtin_echo(&options[1]);
	else if (ft_is_a_match("cd", options[0]) == YES)
		builtin_cd(&options[1]);
	else if (ft_is_a_match("pwd", options[0]) == YES)
		builtin_pwd(&options[1]);
	// else if (ft_is_a_match("export", options[0]) == YES)
	// 	builtin_export(&options[1]);
	// else if (ft_is_a_match("unset", options[0]) == YES)
	// 	builtin_unset(&options[1]);
	else if (ft_is_a_match("env", options[0]) == YES)
		builtin_env(&options[1]);

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