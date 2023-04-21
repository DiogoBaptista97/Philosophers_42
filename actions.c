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
	pthread_mutex_lock(&philo->may_die);
	print_state(get_dif_time(philo->table->time_start), philo, "is eating\n");
	philo->time_after_ate = get_time();
	pthread_mutex_unlock(&philo->may_die);
	usleep(philo->table->time_to_eat * 1000);
	drop_fork(philo);
	//update number eats;
}

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print_state(get_dif_time(philo->table->time_start), philo, "has taken a fork\n");
	print_state(get_dif_time(philo->table->time_start), philo, "has taken a fork\n");

}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_state(get_dif_time(philo->table->time_start), philo, "has drop a fork\n");
	print_state(get_dif_time(philo->table->time_start), philo, "has drop a fork\n");

}

suseconds_t	get_dif_time(suseconds_t prev)
{
	return (get_time() - prev);
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

bool	check_alive_philo(t_philo *philo)
{
	long int last;
	
	last = get_dif_time(philo->time_after_ate);
	if (last > philo->table->time_to_die)
		return (false);
	else
		return (true);
}

void	print_state(suseconds_t time, t_philo *philo, char *str)
{
	printf("%d i tried wright: %s", philo->id, str);
	if (philo->table->deads == true)
		return ;
	pthread_mutex_lock(&philo->table->monitor);
	printf("%ld %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->monitor);

}

/* 
void	check_death(t_table *table, t_philo *philos)
{
	int	i;
	long int last;

 	while (table->must_eat != 0)
	{
		i = 1;
		while (++i < table->number_philos && table->deads == false)
		{
			pthread_mutex_lock(&table->end_sim);//ver se e o monnitor ou end sim
			last = get_dif_time(philos[i].time_after_ate);
//			printf("o %d, last: %ld o que tem para comer: %d\n", philos[i].id ,last, philos[i].table->time_to_die);
			if (last > philos[i].table->time_to_die)
			{
				philos[i].table->deads = true;
				philos[i].alive = false;
			}
			pthread_mutex_unlock(&table->end_sim);
			if ( i == table->number_philos)
				i = -1;
			usleep(1);
		}
	}

} */