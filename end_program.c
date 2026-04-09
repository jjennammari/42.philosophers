/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:48:00 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/08 11:49:58 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < data->philo_amount)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free (data->philos);
	data->forks = NULL;
	data->philos = NULL;
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->end_mutex);
}

bool	ft_has_ended(t_data *data)
{
	bool	value;

	pthread_mutex_lock(&data->end_mutex);
	value = data->end_simulation;
	pthread_mutex_unlock(&data->end_mutex);
	return (value);
}

void	ft_set_end(t_data *data, bool value)
{
	pthread_mutex_lock(&data->end_mutex);
	data->end_simulation = value;
	pthread_mutex_unlock(&data->end_mutex);
}
