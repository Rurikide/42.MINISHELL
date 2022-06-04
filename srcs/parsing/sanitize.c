/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:19:38 by adubeau           #+#    #+#             */
/*   Updated: 2022/06/04 11:51:07 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!dest || !src)
		return (0);
	if (n > 0)
	{
		while (--n && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

int	ft_is_present(char c, char *sym)
{
	int	i;

	i = 0;
	while (sym[i])
	{
		if (sym[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ms_check_pipes(char *input, int i, int r)
{
	int	j;

	j = i;
	while (j > 0 && input[j--])
	{
		if (ft_isalnum(input[j]))
		{
			r += 1;
			break ;
		}
	}
	while (input[i++])
	{
		if (ft_isalnum(input[i]))
		{
			r += 1;
			break ;
		}
	}
	if (r < 2)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		get_minishell()->exit_nb = 258;
	}
	return (r);
}

static int	ft_manage_redir(char *input, int *i, char c)
{
	int	j;

	j = 0;
	while (input[*i] == c)
	{
		j++;
		*i += 1;
	}
	while (input[*i] && !(ft_isalnum(input[*i])))
	{
		*i += 1;
		if (input[*i] == '|')
		{
			get_minishell()->exit_nb = 258;
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	if (ft_strlen(input) == *i || j > 2)
	{
		get_minishell()->exit_nb = 258;
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	ms_sanitize(char *input)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (input[i])
	{
		if (ft_strlen(input) == 1 && (input[i] == '\'' || input[i] == '"'))
        {
            printf("minishell: Error missing %c\n", input[i]);
            return (0);
        }
		if (input[i] == '|')
		{
			r = ms_check_pipes(input, i, 0);
			if (r < 2)
				return (0);
		}
		else if (input[i] == '<' || input[i] == '>')
			if (ft_manage_redir(input, &i, input[i]))
				return (0);
		i++;
	}
	return (1);
}
