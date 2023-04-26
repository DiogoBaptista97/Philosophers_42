/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:53:11 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/03/21 17:53:14 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	iseat(t_philo *philo)
{
	pick_fork(philo);
	pthread_mutex_lock(&philo->table->end_sim);
	print_state(get_dif_time(philo->table->time_start), philo, "is eating\n");
	philo->ate--;
	if (philo->ate == 0)
		philo->table->ate_all++;
	philo->time_after_ate = get_time();
	pthread_mutex_unlock(&philo->table->end_sim);
	usleep(philo->table->time_to_eat * 1000);
	drop_fork(philo);
}

void	pick_fork(t_philo *philo)
{
	if (philo->id == philo->table->number_philos
		&& philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	print_state(get_dif_time(philo->table->time_start),
		philo, "has taken a fork\n");
	print_state(get_dif_time(philo->table->time_start),
		philo, "has taken a fork\n");
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	issleep(t_philo *philo)
{
	print_state(get_dif_time(philo->table->time_start), philo, "is sleeping\n");
	usleep(philo->table->time_to_sleep * 1000);
}

void	isthink(t_philo *philo)
{
	print_state(get_dif_time(philo->table->time_start), philo, "is thinking\n");
}
