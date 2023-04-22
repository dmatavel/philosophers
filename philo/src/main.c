/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmatavel <dmatavel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:00:41 by dmatavel          #+#    #+#             */
/*   Updated: 2023/04/22 20:05:25 by dmatavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	only_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

static int	int_off_limits(char	*s)
{
	int	n;

	n = ft_atoi(s);
	if (n < MIN_NUM_OF_PHILOS
		|| n > MAX_NUM_OF_PHILOS)
		return (TRUE);
	else
		return (FALSE);
}

static int	check_valid_inputs(char **argv)
{
	if ((only_digits(argv) == TRUE)
		&& (int_off_limits(argv[1]) == FALSE))
		return (SUCCESS);
	else
		return (FAILURE);
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
		init_monitor(&data);
		join_threads(&data);
		finish(&data);
	}
	else
	return (FAILURE);
	return (SUCCESS);
}
