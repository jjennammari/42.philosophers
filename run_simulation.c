/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:08:55 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/07 20:10:05 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_start_simulation(t_data *data)
{
	data->start_time = ft_get_time(data);
	return (0);
}

long	ft_get_time(t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (time);
}
