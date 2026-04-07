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

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5  || ac == 6)
	{
		if (parse_input(av, ac))
			return (printf("Error: use only digits in the input and\
				values bigger than 0"), 1);
		if (init_variables(&data, av, ac))
			return (clear_data(&data), 1);
		start_simulation(&data);
		clear_data(&data);
	}
	else
		return (printf("Error: execute program with 5 or 6 arguments:\
			philos, deth time, eating time, sleeping time, [max eat]"), 1);
	return (0);
}
