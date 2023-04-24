/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:13:42 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/03/15 10:13:43 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	shut_down(t_table *table, t_philo *philo)
{
	int i;
	int	max_id;

	max_id = table->number_philos;

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
/*		i = -1;
 		while (++i < table->number_philos)
			free(&table->forks[i]); */
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->end_sim);
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
	free(table);
	exit(EXIT_SUCCESS);
}

bool	start(t_table *table, char **argv, int argc)
{
	int	i;

	table->number_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->time_start = get_time();
	table->deads = false;
	table->ate_all = 0;
	if (argc == 5)
		table->must_eat = -1;
	else
		table->must_eat = ft_atoi(argv[5]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philos);
	i = -1;
	while (++i < table->number_philos)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->monitor, NULL);
	pthread_mutex_init(&table->end_sim, NULL);
	pthread_mutex_init(&table->check_dead, NULL);
	return (true);
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
		pthread_create(&philos[i].phi, NULL, routine, (void *)&philos[i]);
	}
//	usleep(10000);
	return (philos);
}

bool	start_threads(t_table *table, t_philo *philo)
{
	int	i;
	if (!creat_monitor_guy(table , table->forks, philo))
		error_msg("faleceu o moitoring\n");
	i = -1;
	while (++i < table->number_philos)
		pthread_join(philo[i].phi, NULL);
	return (true);
}

bool	creat_monitor_guy(t_table *table, pthread_mutex_t *forks, t_philo *philos)
{
	(void )forks;
	pthread_create(&table->superv, NULL, rout_mon, (void *)&*philos);
	pthread_join(table->superv, NULL);
	return(true);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;
	t_philo *philo;

	i = -1;
	if (argc != 5 && argc != 6)
		error_msg("In put is incorrect, but be: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_pholosopher_must_eat]\n");
	if (checkdigit(argv) == false)
		error_msg("must be a number\n");
	table = malloc(sizeof(t_table));
	if (start(table, argv, argc) != true)
		printf("Error\n");
	philo = start_philos(table, argv);
	if (!start_threads(table, philo))
		return (EXIT_FAILURE);
	if (!philo)
		printf("error2\n");
	shut_down(table, philo);
	return (0);
}
