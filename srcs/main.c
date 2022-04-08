#include "builtins.h"

// function searches value of variable in the env
char	*env_var_get_value(char *key, size_t size)
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
char	*env_var_get_key_value(char *key, size_t size)
{
	t_minishell *ms;

	ms = get_minishell();

	if (*ms->env == NULL)
		return (NULL);

	while (*ms->env != NULL)
	{
		if (ft_strncmp(*ms->env, key, size) == SUCCESS)
		{
			printf("%s\n", *ms->env);
			return (*ms->env);
		}

		else
			ms->env++;
	}
	return (NULL);
}

int	env_var_get_key_index(char *key, size_t size)
{
	t_minishell *ms;
	int		i;

	i = 0;
	ms = get_minishell();
	while (ms->env[i] != NULL)
	{
		if (ft_strncmp(ms->env[i], key, size) == SUCCESS)
		{
			//printf("%s\n", ms->env[i]);
			//printf("%d\n", i);
			return (i);
		}
		i++;
	}
	return (FAIL);
}

// // function updating an env var
void	env_var_update(char *key, size_t size, char *update)
{
	size_t i;

	i = 0;

	// FAIRE UN CHECK SI LA VARIABLE NEXISTE PAS
	i = env_var_get_key_index(key, size);
	get_minishell()->env[i] = ft_strjoin(key, update);
//	get_minishell()->env[i] = ft_strdup(update);
}

// function to malloc minishell->env with the env from the main
void	init_env(char **env)
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
}

void	env_var_print(void)
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