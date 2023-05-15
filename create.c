/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:45:28 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/04/24 12:45:29 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	shut_down(t_table *table, t_philo *philo)
{
	int	i;

	i = -1;
	if (table->forks)
	{
		while (++i < table->number_philos)
		{
			pthread_mutex_destroy(&philo[i].may_die);
			pthread_mutex_destroy(&table->forks[i]);
			philo[i].left_fork = NULL;
			philo[i].right_fork = NULL;
		}
		free(table->available);
		free(table->forks);
		table->forks = NULL;
	}
	destroy_mut(table);
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
	free(table);
}

void	destroy_mut(t_table *table)
{
	pthread_mutex_destroy(&table->monitor);
	pthread_mutex_destroy(&table->end_sim);
	pthread_mutex_destroy(&table->lock_fork);
	pthread_mutex_destroy(&table->check_dead);
}

void	creat_forks(t_table *table)
{
	int	i;

	table->available = malloc(sizeof(bool) * table->number_philos);
	i = -1;
	while (++i < table->number_philos)
		table->available[i] = true;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philos);
	i = -1;
	while (++i < table->number_philos)
		pthread_mutex_init(&table->forks[i], NULL);
}

t_philo	*start_philos(t_table *table, char **argv)
{
	int		i;
	t_philo	*philos;

	(void)argv;
	philos = malloc(sizeof(t_philo) * (table->number_philos));
	i = -1;
	while (++i < table->number_philos)
	{
		pthread_mutex_init(&philos[i].may_die, NULL);
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[(i + 1) % table->number_philos];
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].ate = table->must_eat;
		philos[i].state = thinking;
		philos[i].time_after_ate = get_time();
	}
	i = -1;
	while (++i < table->number_philos)
	{
		pthread_create(&philos[i].phi, NULL, routine, (void *)&philos[i]);
		usleep(2000);
	}
	return (philos);
}

bool	creat_monitor_guy(t_table *table,
							pthread_mutex_t *forks, t_philo *philos)
{
	(void )forks;
	pthread_create(&table->superv, NULL, rout_mon, (void *)&*philos);
	pthread_join(table->superv, NULL);
	return (true);
}
