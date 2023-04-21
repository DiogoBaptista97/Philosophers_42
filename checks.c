/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:31:06 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/03/22 11:31:07 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_long_atoi(char *str)
{
	int		j;
	int  sinal;
	long	res;

	sinal = 1;
	res = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if ((*str == '-' || *str == '+') && (*str))
	{
		if (*str == '-')
		{
			sinal = sinal * (-1);
		}
		if (*str != '-' && *str != '+')
			return (0);
		str++;
	}
	j = 0;
	while ((str[j] >= '0' && str[j] <= '9') && str[j] != 0)
	{	
		res = (res * 10) + (str[j] - '0');
		j++;
	}
	return (res * sinal);
}

bool	checkdigit_aux(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '-' || str[i] == '+') && (str[i]))
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (false);
		i++;
	}
	return (true);
}

bool	checkdigit(char *argv[])
{
	int		i;
	int		j;
	long	num;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (checkdigit_aux(argv[i]) == false)
			return (false);
		num = ft_long_atoi(argv[i]);
		if (num > INT_MAX || num < INT_MIN)
			return (false);
		i++;
	}
	return (true);
}

void	error_msg(char *msg)
{
	int	i;

	i = -1;
	while (msg[++i])
		write(1, &msg[i], 1);
	exit(EXIT_FAILURE);
}
