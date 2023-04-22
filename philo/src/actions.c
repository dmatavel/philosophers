/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:04:22 by dmatavel          #+#    #+#             */
/*   Updated: 2023/04/22 20:09:04 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_dead_philo(t_philo *philo, char *action)
{
	printf("%lu\t%d\t%s\n", time_now(philo),
			philo->id, action);
}

void	print_action(t_philo *philo, char *action)
{
	printf("%lu\t%d\t%s\n", time_now(philo),
			philo->id, action);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	philo->meals_counter += 1;
	philo->last_meal = time_now(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}