/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:40:39 by dmatavel          #+#    #+#             */
/*   Updated: 2023/04/28 12:06:54 by dmatavel         ###   ########.fr       */
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
	if ((philo->id % 2) == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock_meal);	
		if (philo->meals_counter == philo->data->must_eat)
		{
			pthread_mutex_unlock(&philo->data->lock_meal);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->lock_meal);
		pthread_mutex_lock(&philo->data->lock_died);
		if (philo->data->died == 1)
			break ;
		pthread_mutex_unlock(&philo->data->lock_died);
		actions(philo);
	}
	pthread_mutex_unlock(&philo->data->lock_meal);
	pthread_mutex_unlock(&philo->data->lock_died);

	return (NULL);
}