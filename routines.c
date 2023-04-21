/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:42:41 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/04/14 17:42:42 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void	*temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	while (philo->table->deads == false)
	{
		printf("sleep %d\n", philo->id);
		iseat(philo);	
		issleep(philo);
		isthink(philo);
	}
	return (NULL);
}

void	*rout_mon(void	*temp)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)temp;
	while (philo->table->must_eat != 0)
	{
		i = -1;
		while (++i < philo->table->number_philos)
		{
			pthread_mutex_lock(&philo[i].table->end_sim);
			if (check_alive_philo(&philo[i]) == false)
			{
				print_state(get_dif_time(philo->table->time_start), &philo[i], "has died\n");
				philo[i].table->deads = true;
				pthread_mutex_unlock(&philo[i].table->end_sim);
//				pthread_mutex_unlock(&philo[i].table->monitor);
//				shut_down(philo->table, philo);
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].table->end_sim);
			//TODO diminui must_eat;
		}
	}
	printf("TODOS COMERAM E NENHUM FOI DEAD\n");
	return (NULL);
}