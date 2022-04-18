
#include "builtins.h"

t_minishell	*get_minishell(void)
{
	static t_minishell minishell;

	if (minishell.init != 1)
	{
		minishell.init = 1;
		minishell.shlvl = 1;
		minishell.env = NULL;
		minishell.env_size = 0;
		minishell.exit_nb = 0;
	}
	return (&minishell);
}

void	scan_builtins(char **options)
{
	if (ft_is_a_match("echo", options[0]) == YES)
		builtin_echo(&options[1]);
	else if (ft_is_a_match("cd", options[0]) == YES)
		builtin_cd(&options[1]);
	else if (ft_is_a_match("pwd", options[0]) == YES)
		builtin_pwd(&options[1]);
	else if (ft_is_a_match("export", options[0]) == YES)
		builtin_export(&options[1]);
	else if (ft_is_a_match("unset", options[0]) == YES)
		builtin_unset(&options[1]);
	else if (ft_is_a_match("env", options[0]) == YES)
		builtin_env(&options[1]);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell *minishell;
	char *str;
	char **options;

	init_env(env);
	minishell = get_minishell();

	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
	// ALEX VA PARSER STR

		options = ft_split(str, ' ');
		scan_builtins(options);

		//printf("%s\n", str);
	}

	ft_free_table(options);
	// readline il faut free
	// ne pas oublier de free str
	return (0);
}