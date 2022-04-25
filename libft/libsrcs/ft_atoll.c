/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:38:49 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/25 16:02:43 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


long long	ft_atoll(const char *str)
{
	long long	nb;
	int			sign;

	nb = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*(str) - 48);
		str++;
	}
	return (nb * sign);
}

// int	ft_isllong(char *str)
// {
// 	long long res;

// 	res = ft_atoll(str);

// 	if (res < LONG_MIN|| res > LONG_MAX)
// 		return (-1);
// 	return (0);
// }

int	ft_isllong(char *str)
{
	char *llmax;
	
	if (*str == '-')
	{
		str++;
		llmax = "9223372036854775808";
	}
	else 
		llmax = "9223372036854775807";
	if (ft_strlen(str) > 19)
		return (-1);
	else if (ft_strlen(str) == 19)
	{
		while(*str)
		{
			if (*str < *llmax)
				return (0);
			else if (*str > *llmax)
				return (-1);
			str++;
			llmax++;
		}
	}
	return (0);
}





	// if (ft_strlen(str) > 19)
	// 	return (-1);

	// if (str[0] == '-' && ft_strlen(str) >= 20 && ft_strcmp(&str[1], "9223372036854775808") > 0)
	// 	return (-1);

	// else if (ft_strlen(str) >= 19 && ft_strcmp(str, "9223372036854775807") > 0)
	// 	return (-1);

	// return (0);
