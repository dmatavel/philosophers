/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:52:05 by dmatavel          #+#    #+#             */
/*   Updated: 2023/04/22 20:15:56 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define FAILURE 1
# define SUCCESS 0
# define MIN_NUM_OF_PHILOS 1
# define MAX_NUM_OF_PHILOS 200

typedef	pthread_mutex_t mtx;
typedef struct	s_philo t_philo;
typedef struct	s_data t_data;

typedef struct	s_philo
{
	unsigned long	start_time;
	unsigned long	last_meal;
	int				meals_counter;
	int				id;
	pthread_t		thread;
	mtx				*left_fork;
	mtx				*right_fork;
	t_data			*data;
}						t_philo;

typedef struct	s_data
{
	int				n_philos;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	unsigned long	start_time;
	int				died;
	int				done;
	t_philo			*philo;
	mtx				*fork;
	mtx				lock_died;
	mtx				lock_meal;
	mtx				lock_done;
}						t_data;

/* utils.c */
int	ft_isdigit(int c);
int	ft_isspace(int c);
int	ft_atoi(const char *str);

/* init.c */
void	init_data(t_data *data, int argc, char **argv);
void	init_philos(t_data *data);
void	init_mutexes(t_data *data);
void	join_threads(t_data *data);
void	init(t_data *data, int argc, char **argv);
int		init_monitor(t_data *data);

/* routine.c */
void	*routine(void *ph);

/* actions.c */
void	print_dead_philo(t_philo *philo, char *action);
void	print_action(t_philo *philo, char *str);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);

/* time.c */
unsigned long	get_current_time(void);
unsigned long	time_now(t_philo *philo);

/* finish.c */
void	destroy_mutexes(t_data *data);
void	detach_threads(t_data *data);
void	clear_memory(t_data *data);
void	finish(t_data *data);

#endif
