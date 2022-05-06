
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
		minishell.user_input = NULL;
		minishell.options = NULL;
		minishell.head = NULL;
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
	else if (ft_is_a_match("exit", options[0]) == YES)
		builtin_exit(&options[1]);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell *minishell;
	//char **options;

	(void)argv;
	(void)argc;
	init_env(env);
	minishell = get_minishell();

	while (true)
	{
		if (minishell->user_input != NULL)
			free(minishell->user_input);
		minishell->user_input = readline("minishell> ");
		add_history(minishell->user_input);
		if (minishell->options != NULL)
			ft_free_table(minishell->options);
		ms_parsing();
		/*options = ft_split(minishell->user_input, ' ');
		minishell->options = options;
		scan_builtins(options);*/
	}
	return (0);
}
