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

/* 	if (try_take_forks(philo) == true)
	{
		pthread_mutex_lock(&philo->table->end_sim);
		philo->state = eating;
		print_state(get_dif_time(philo->table->time_start), philo, "is eating\n");
		philo->ate--;
		if (philo->ate == 0)
			philo->table->ate_all++;
		philo->time_after_ate = get_time();
		pthread_mutex_unlock(&philo->table->end_sim);
		usleep(philo->table->time_to_eat * 1000);
	} */
void	iseat(t_philo *philo)
{
	pick_fork(philo);
	pthread_mutex_lock(&philo->table->end_sim);
	philo->state = eating;
	print_state(get_dif_time(philo->table->time_start), philo, "is eating\n");
	philo->ate--;
	if (philo->ate == 0)
		philo->table->ate_all++;
	philo->time_after_ate = get_time();
	pthread_mutex_unlock(&philo->table->end_sim);
	usleep(philo->table->time_to_eat * 1000);
}

void	pick_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else if (philo->id % 2 == 0)
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
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	issleep(t_philo *philo)
{
	philo->state = sleeping;
	drop_fork(philo);
	print_state(get_dif_time(philo->table->time_start), philo, "is sleeping\n");
	usleep(philo->table->time_to_sleep * 1000);
}

void	isthink(t_philo *philo)
{
	philo->state = thinking;
	print_state(get_dif_time(philo->table->time_start), philo, "is thinking\n");
}
