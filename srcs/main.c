#include "../incls/builtins.h"
#include <unistd.h>

// function searches value of variable in the env
char	*get_env_var_value(char *key, size_t size)
{
	t_minishell *ms;

	ms = get_minishell();

	if (ms->env == NULL)
		return (NULL);

	while (ms->env != NULL)
	{
		if (ft_strncmp(*ms->env, key, size) == SUCCESS)
			return (&(*ms->env)[size]);
			// return the value after the '='
		else
			ms->env++;
	}
	return (NULL);
}

// function return the whole env var. ex HOME=usr/
char	*get_env_var_key(char *key, size_t size)
{
	t_minishell *ms;

	ms = get_minishell();

	if (ms->env == NULL)
		return (NULL);

	while (ms->env != NULL)
	{
		if (ft_strncmp(*ms->env, key, size) == SUCCESS)
			return (*ms->env);

		else
			ms->env++;
	}
	return (NULL);
}


// // function updating an env var
void	ft_env_var_update(char *key, size_t size, char *value)
{
	size_t i;

	i = 0;


}

// function to malloc minishell->env with the env from the main
void	ft_init_env(char **env)
{
	t_minishell *minishell;
	size_t nb;

	nb = 0;
	while (env[nb] != NULL)
		nb++;
	minishell = get_minishell();
	minishell->env_size = nb + 1;
	minishell->env = malloc((sizeof(char *)) * (nb + 1));
	nb = 0;
	while (env[nb] != NULL)
	{
		minishell->env[nb] = ft_strdup(env[nb]);
		nb++;
	}
	minishell->env[nb] = NULL;
	ft_env_var_flaunt();
}

void	ft_env_var_flaunt(void)
{
	t_minishell *minishell;
	size_t i;

	i = 0;
	minishell = get_minishell();
	while (minishell->env[i] != NULL)
	{
		printf("%s\n", minishell->env[i]);
		i++;
	}
}

t_minishell	*get_minishell(void)
{
	static t_minishell minishell;

	if (minishell.init != 1)
	{
		minishell.init = 1;
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