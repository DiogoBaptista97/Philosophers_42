/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <dbraga-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:07:30 by dbraga-b          #+#    #+#             */
/*   Updated: 2022/11/14 16:03:03 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	j;
	int	sinal;
	int	res;

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

suseconds_t	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n > 2147483647)
		return ;
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n < 10)
	{
		ft_putchar_fd((n + '0'), fd);
		return ;
	}
	ft_putnbr_fd((n / 10), fd);
	ft_putchar_fd((n % 10 + '0'), fd);
}