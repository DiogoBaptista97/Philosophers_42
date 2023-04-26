/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:53:27 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/04/24 12:53:28 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_dif_time(suseconds_t prev)
{
	return (get_time() - prev);
}

bool	check_alive_philo(t_philo *philo)
{
	long int	last;

	last = get_dif_time(philo->time_after_ate);
	if (last > philo->table->time_to_die)
		return (false);
	else
		return (true);
}

void	print_state(suseconds_t time, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if (philo->table->deads == true || philo->ate == 0)
	{
		pthread_mutex_unlock(&philo->table->check_dead);
		return ;
	}
	pthread_mutex_lock(&philo->table->monitor);
	printf("%ld %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->monitor);
	pthread_mutex_unlock(&philo->table->check_dead);
}
