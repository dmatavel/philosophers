/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:40:39 by dmatavel          #+#    #+#             */
/*   Updated: 2023/04/24 17:32:59 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	one_philo_case(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	print_action(philo, "died");
}

void	actions(t_philo *philo)
{	
	ft_eat(philo);
	ft_sleep(philo);
	ft_think(philo);
}

void	*routine(t_philo *philo)
{
	if (philo->data->n_philos > 1)
	{
		if ((philo->id % 2) == 0)
			usleep(100);
		while (1)
		{
			pthread_mutex_lock(&philo->data->lock_died);
			if (philo->data->died == 1)
				break ;
			pthread_mutex_unlock(&philo->data->lock_died);
			pthread_mutex_unlock(&philo->data->lock_done);
			if (philo->data->must_eat == philo->meals_counter)
			{
				philo->data->done += 1;
				pthread_mutex_unlock(&philo->data->lock_done);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->data->lock_done);
			actions(philo);
		}
		pthread_mutex_unlock(&philo->data->lock_died);
	}
	return (NULL);
}