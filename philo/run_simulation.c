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

int		ft_run_simulation(t_data *data);
void	ft_init_last_meals(t_data *data);
int		ft_create_threads(t_data *data, long *created);
void	ft_join_threads(t_data *data, long created);
void	ft_sleep_ms(t_data *data, long time_ms);

int	ft_run_simulation(t_data *data)
{
	long	created;

	data->start_time = ft_get_time_ms();
	ft_init_last_meals(data);
	pthread_mutex_lock(&data->start_mutex);
	created = 0;
	if (ft_create_threads(data, &created) != 0)
	{
		ft_set_end(data, true);
		ft_join_threads(data, created);
		return (printf("Error: thread creation failed"), -1);
	}
	data->start_time = ft_get_time_ms();
	pthread_mutex_unlock(&data->start_mutex);
	ft_monitor(data);
	ft_join_threads(data, data->philo_amount);
	return (0);
}

void	ft_init_last_meals(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->philo_amount)
	{
		data->philos[i].last_meal_ms = data->start_time;
		i++;
	}
}

int	ft_create_threads(t_data *data, long *created)
{
	long	i;

	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				ft_routine, &data->philos[i]) != 0)
			return (-1);
		i++;
	}
	*created = i;
	return (0);
}

void	ft_join_threads(t_data *data, long created)
{
	long	i;

	i = 0;
	while (i < created)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

void	ft_sleep_ms(t_data *data, long time_ms)
{
	long	start;

	start = ft_get_time_ms();
	while (!ft_has_ended(data))
	{
		if (ft_get_time_ms() - start >= time_ms)
			break ;
		usleep(500);
	}
}
