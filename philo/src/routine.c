/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:40:39 by dmatavel          #+#    #+#             */
/*   Updated: 2023/04/22 20:21:26 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *ph)
{
	t_philo	*philo;
	
	philo = (t_philo *)ph;
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
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	pthread_mutex_unlock(&philo->data->lock_died);
	return (NULL);
}