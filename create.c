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
	pthread_mutex_destroy(&table->monitor);
	if (table->forks)
	{
		while (++i < table->number_philos)
		{
			pthread_mutex_destroy(&philo[i].may_die);
			pthread_mutex_destroy(&table->forks[i]);
			philo[i].left_fork = NULL;
			philo[i].right_fork = NULL;
		}
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->end_sim);
	pthread_mutex_destroy(&table->lock_fork);
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
	free(table);
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

	i = -1;
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
		philos[i].time_after_ate = table->time_start;
		philos[i].r = i;
		philos[i].l = (i + 1) % table->number_philos;
		pthread_create(&philos[i].phi, NULL, routine, (void *)&philos[i]);
		usleep(1000);
	}
	return (philos);
}

bool	start_threads(t_table *table, t_philo *philo)
{
	int	i;

	if (!creat_monitor_guy(table, table->forks, philo))
		error_msg("faleceu o moitoring\n");
	usleep(1000);
	i = -1;
	while (++i < table->number_philos)
		pthread_join(philo[i].phi, NULL);
	return (true);
}

bool	creat_monitor_guy(t_table *table,
							pthread_mutex_t *forks, t_philo *philos)
{
	(void )forks;
	pthread_create(&table->superv, NULL, rout_mon, (void *)&*philos);
	pthread_join(table->superv, NULL);
	return (true);
}
