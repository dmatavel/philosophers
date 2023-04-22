/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:11:37 by dmatavel          #+#    #+#             */
/*   Updated: 2023/04/22 20:17:23 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->n_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->start_time = get_current_time();
	data->died = 0;
	data->done = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	data->fork = malloc(sizeof(t_philo) * data->n_philos);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{	
		data->philo[i].right_fork = &data->fork[i];
		if (i == (data->n_philos - 1))
			data->philo[i].left_fork = &data->fork[0];
		else
			data->philo[i].left_fork = &data->fork[i + 1];
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].meals_counter = 0;
		data->philo[i].data = data;
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
}

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->lock_died, NULL);
	pthread_mutex_init(&data->lock_meal, NULL);
	pthread_mutex_init(&data->lock_done, NULL);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join((pthread_t)data->philo[i].thread, NULL);
		i++;
	}
}

int	init_monitor(t_data *data)
{
    int i;

    i = 0;
	usleep(100);
    while (1)
    {
		if (i == data->n_philos)
			i = 0;
		
		if (data->done == data->n_philos)
			break ;
		pthread_mutex_lock(&data->lock_meal);
        if ((time_now(&data->philo[i]) - data->philo[i].last_meal) >= data->time_to_die)
		{
			pthread_mutex_lock(&data->lock_died);
            data->died = 1;
			print_dead_philo(&data->philo[i], "died");
			pthread_mutex_unlock(&data->lock_died);
			pthread_mutex_unlock(&data->lock_meal);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&data->lock_meal);
		usleep(100);
	}
	return (0);
}