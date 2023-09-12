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

bool	start(t_table *table, char **argv, int argc)
{
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
	creat_forks(table);
	pthread_mutex_init(&table->monitor, NULL);
	pthread_mutex_init(&table->end_sim, NULL);
	pthread_mutex_init(&table->check_dead, NULL);
	pthread_mutex_init(&table->lock_fork, NULL);
	return (true);
}

bool	start_threads(t_table *table, t_philo *philo)
{
	int	i;

	if (!creat_monitor_guy(table, table->forks, philo))
		error_msg("faleceu o moitoring\n");
	i = -1;
	while (++i < table->number_philos)
		pthread_join(philo[i].phi, NULL);
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;
	t_philo	*philo;

	i = -1;
	if (argc != 5 && argc != 6)
		error_msg("Input is incorrect\n");
	if (checkdigit(argv) == false)
		error_msg("must be a number ou positive\n");
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
