/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:14:54 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/03/15 10:14:55 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>

//info for all philosophers
typedef struct s_table{
	int				number_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	suseconds_t		time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	monitor;
	pthread_mutex_t	end_sim;
	pthread_mutex_t check;
	bool			deads;
	pthread_t		superv;
}	t_table;

//info in a philo
typedef struct s_philo{
	pthread_t	phi;
	int			id;
	int			ate;
	suseconds_t	time_after_ate;
	t_table		*table;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t may_die;
}	t_philo;

//define the forks and is states
//time eating
//time thinking
//time sleeping
//keep tracks of forks in each side
//time fasting
//

suseconds_t	get_time(void);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(char *str);
void		ft_putnbr_fd(int n, int fd);
void		iseat(t_philo *philo);
void		issleep(t_philo *philo);
void		isthink(t_philo *philo);
long		ft_long_atoi(char *str);
bool		checkdigit_aux(char *str);
bool		checkdigit(char *argv[]);
void		error_msg(char *msg);
suseconds_t	get_dif_time(suseconds_t prev);
bool		check_alive_philo(t_philo *philo);
void		shut_down(t_table *table, t_philo *philo);
void		print_state(suseconds_t time, t_philo *philo, char *str);
bool		check_death(t_philo *philo);
void		*routine(void	*temp);
void		*rout_mon(void	*temp);
bool		creat_monitor_guy(t_table *table, pthread_mutex_t *forks, t_philo *philos);
void		pick_fork(t_philo *philo);
void		drop_fork(t_philo *philo);
#endif
