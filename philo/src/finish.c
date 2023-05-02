/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:08:58 by dmatavel          #+#    #+#             */
/*   Updated: 2023/05/02 14:15:43 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock_died);
	pthread_mutex_destroy(&data->lock_meal);
	pthread_mutex_destroy(&data->lock_print);
}

void	detach_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_detach((pthread_t)data->philo[i].thread);
		i++;
	}
}

void	clear_memory(t_data *data)
{
	if (data->fork != NULL)
		free(data->fork);
	if (data->philo != NULL)
		free(data->philo);
	if	(data != NULL)
		free(data);
}

void	finish(t_data *data)
{
	destroy_mutexes(data);
	detach_threads(data);
	clear_memory(data);
}
