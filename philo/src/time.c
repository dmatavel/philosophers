/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:53:50 by dmatavel          #+#    #+#             */
/*   Updated: 2023/05/02 13:06:13 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long	get_current_time(void)
{
	struct timeval	current_time;
	unsigned long	time_in_ms;

	gettimeofday(&current_time, NULL);
	time_in_ms = (current_time.tv_sec * 1000) \
				+ (current_time.tv_usec / 1000);
	return (time_in_ms);
}

unsigned long	time_now(t_philo *philo)
{
	return (get_current_time() - philo->data->start_time);
}

void	smart_sleep(unsigned long time, t_philo *philo)
{
	unsigned long	end_time;

	end_time = time_now(philo) + time;
	while (end_time > time_now(philo))
	{
		usleep(100);
		pthread_mutex_lock(&philo->data->lock_died);
		if (philo->data->died == 1)
		{
			pthread_mutex_unlock(&philo->data->lock_died);
			return ;
		}
		pthread_mutex_unlock(&philo->data->lock_died);
	}
}
