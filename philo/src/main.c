/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:00:41 by dmatavel          #+#    #+#             */
/*   Updated: 2023/04/28 14:09:49 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	only_digits(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	int_off_limits(char	*s)
{
	long	n;
	long	i;

	i = 0;
	while (s[i])
	{
		n = ft_atol(s);
		if (n >= MIN_NUM_OF_PHILOS
			&& n <= INT_MAX)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	check_valid_inputs(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!only_digits(&argv[i][0])
			|| int_off_limits(&argv[i][0]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc == 5 || argc == 6)
		&& (check_valid_inputs(argv) == SUCCESS))
	{
		init_data(&data, argc, argv);
		init_mutexes(&data);
		init_philos(&data);
		if (data.n_philos == 1)
		{
			one_philo_case(data.philo);
			return (SUCCESS);
		}
		else
			init_monitor(&data, 0);
		join_threads(&data);
		finish(&data);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
