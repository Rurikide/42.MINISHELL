/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:42:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/30 17:20:58 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void mise_en_abyme(char **options)
{
	pid_t process_id;

	process_id = fork();

	if (process_id == SUCCESS)
	{
		execve(*options, options, get_minishell()->env);
		printf("hello from child process\n");
	}
	else 
		waitpid(process_id, NULL, 0);
}

// access() doit pouvoir accepter un path dès le départ par exemple : /bin/ls


/* MON PIPEX 

t_result	ft_is_valid_command(t_container *input, int i, char *cmd)
{
	size_t	nb;

	nb = 0;
	while (input->bins[nb] != NULL)
	{
		input->cmd[i].path = ft_strjoin_symbol(input->bins[nb], '/', cmd);
		if (access(input->cmd[i].path, F_OK) == SUCCESS)
			return (SUCCESS);
		free(input->cmd[i].path);
		nb++;
	}
	return (FAIL);
}

char	*ft_find_path_variable(t_container *input)
{
	if (input->envp == NULL)
		return (NULL);
	while (input->envp != NULL)
	{
		if (ft_strncmp(*input->envp, "PATH=", 5) == SUCCESS)
			return (&(*input->envp)[6]);
		else
			input->envp++;
	}
	return (NULL);
}

void	ft_parse_command_line(t_container *input)
{
	int	i;

	i = 1;
	input->bins = ft_split(ft_find_path_variable(input), ':');
	if (input->bins == NULL)
	{
		ft_printf("Error path variable is NULL\n");
		ft_free_table(input->bins);
		free(input->cmd);
		exit(EXIT_FAILURE);
	}
	while (input->argv[i] && input->argv[i + 1])
	{
		input->cmd[i].param = ft_split(input->argv[i], ' ');
		if (input->cmd[i].param == NULL)
			ft_perror_cmd_free(input, i, "Error split cmd");
		if (ft_is_valid_command(input, i, input->cmd[i].param[0]) == FAIL)
		{
			ft_printf("cmd #%d is invalid.\n", i);
			ft_perror_cmd_free(input, i, "Error parse cmd");
		}
		i++;
	}
}

void	ft_perror_nl_free(t_container *input, int i, char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	while (i >= 1)
	{
		ft_free_table(input->cmd[i].param);
		free(input->cmd[i].path);
		i--;
	}
	ft_free_table(input->bins);
	free(input->cmd);
	exit(EXIT_FAILURE);
}

void	ft_perror_cmd_free(t_container *input, int i, char *message)
{
	int	j;

	j = 1;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	while (j <= i)
	{
		ft_free_table(input->cmd[j].param);
		if (j < i)
			free(input->cmd[j].path);
		j++;
	}
	ft_free_table(input->bins);
	free(input->cmd);
	exit(EXIT_FAILURE);
}

void	free_container(t_container *input)
{
	int	i;

	i = 1;
	while (i < input->argc - 1)
	{
		ft_free_table(input->cmd[i].param);
		free(input->cmd[i].path);
		i++;
	}
	ft_free_table(input->bins);
	free(input->cmd);
}

void	ft_pipe_x_process(t_container *input, int i, int i_fd, int o_fd)
{
	int		pipe_end[2];
	pid_t	res_pid;

	if (pipe(pipe_end) == FAIL)
		ft_perror_nl_free(input, input->argc - 2, "Error creating pipe");
	dup2(i_fd, 0);
	close(i_fd);
	if (i == input->argc - 2)
		dup2(o_fd, 1);
	else
		dup2(pipe_end[1], 1);
	res_pid = fork();
	if (res_pid == FAIL)
		ft_perror_nl_free(input, input->argc - 2, "Fork failure");
	if (res_pid == SUCCESS)
		execve(input->cmd[i].path, input->cmd[i].param, input->envp);
	else
	{
		close(pipe_end[1]);
		waitpid(res_pid, NULL, 0);
	}
	if (i < input->argc - 2)
		return (ft_pipe_x_process(input, i + 1, pipe_end[0], o_fd));
}

void	ft_prepare_x_process(t_container *input)
{
	int	i_fd;
	int	o_fd;
	int	i;

	if (ft_strdouble(input->argv[0], input->argv[input->argc - 1]) == true)
		ft_perror_nl_free(input, input->argc - 2, "Files must be different");
	o_fd = open(input->argv[input->argc - 1], \
		O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (o_fd == FAIL)
		ft_perror_nl_free(input, input->argc - 2, "Error writing result file");
	i_fd = open(input->argv[0], O_RDONLY, 0777);
	if (i_fd == FAIL)
		ft_perror_nl_free(input, input->argc - 2, "Error reading source file");
	i = 1;
	ft_pipe_x_process(input, i, i_fd, o_fd);
}

*/