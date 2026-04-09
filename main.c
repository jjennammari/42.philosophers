/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:49:41 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/05 18:53:58 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print(t_data *data)
{
	printf("philo_amount=%ld\n", data->philo_amount);
	printf("time_to_die=%ld ms\n", data->time_to_die);
	printf("time_to_eat=%ld ms\n", data->time_to_eat);
	printf("time_to_sleep=%ld ms\n", data->time_to_sleep);
	printf("max_meals=%ld\n", data->max_meals);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5  || ac == 6)
	{
		if (ft_parse_input(av, ac))
			return (1);
		if (ft_init_variables(&data, av, ac))
			return (ft_clear_data(&data), 1);
		ft_print(&data);
		ft_run_simulation(&data);
		ft_clear_data(&data);
	}
	else
		return (printf("Error: execute program with 5 or 6 arguments:\
			philos, deth time, eating time, sleeping time, [max eat]"), 1);
	return (0);
}
