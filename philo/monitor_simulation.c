/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:55:07 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/09 14:07:11 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_monitor(t_data *data);
int		ft_check_full(t_data *data);
int		ft_check_death(t_data *data);
int		ft_end_print_death(t_data *data, long i);
long	ft_get_time_ms(void);

void	ft_monitor(t_data *data)
{
	while (!ft_has_ended(data))
	{
		if (ft_check_death(data))
			break ;
		if (ft_check_full(data))
			break ;
		usleep(1000);
	}
}

int	ft_check_full(t_data *data)
{
	long	i;
	long	full_count;
	long	meals;

	if (data->max_meals == -1)
		return (0);
	full_count = 0;
	i = 0;
	while (i < data->philo_amount)
	{
		pthread_mutex_lock(&data->meal_mutex[i]);
		meals = data->philos[i].meals_eaten;
		pthread_mutex_unlock(&data->meal_mutex[i]);
		if (meals >= data->max_meals)
			full_count++;
		i++;
		usleep(50);
	}
	if (full_count == data->philo_amount)
	{
		ft_set_end(data, true);
		return (1);
	}
	return (0);
}

int	ft_check_death(t_data *data)
{
	long	i;
	long	now;
	long	last;

	now = ft_get_time_ms();
	i = 0;
	while (i < data->philo_amount)
	{
		pthread_mutex_lock(&data->meal_mutex[i]);
		last = data->philos[i].last_meal_ms;
		pthread_mutex_unlock(&data->meal_mutex[i]);
		if (now - last >= data->time_to_die)
			return (ft_end_print_death(data, i));
		i++;
		usleep(50);
	}
	return (0);
}

int	ft_end_print_death(t_data *data, long i)
{
	long	now;

	pthread_mutex_lock(&data->end_mutex);
	if (data->end_simulation)
	{
		pthread_mutex_unlock(&data->end_mutex);
		return (1);
	}
	data->end_simulation = 1;
	pthread_mutex_lock(&data->print_mutex);
	now = ft_get_time_ms();
	printf("%ld %d died\n", now - data->start_time, data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&data->end_mutex);
	return (1);
}

long	ft_get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}
