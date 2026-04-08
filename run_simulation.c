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
	long	i;

	data->start_time = ft_get_time_ms();
	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, ft_routine, &data->philos[i]) != 0)
			return (printf("Error: thread creation failed"), -1);
		i++;
	}
	i = 0;
	while (i < data->philo_amount)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}

long	ft_get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	ft_sleep_ms(t_data *data, long time_ms)
{
	long	start;

	start = ft_get_time_ms();
	while (!ft_has_ended(data))
	{
		if (ft_get_time_ms() - start >= time_ms)
			break ;
		usleep(200);
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!ft_has_ended(philo->data))
	{
		ft_take_forks(philo);
		ft_print_simulation(philo->data, philo->id, "is eating");
		ft_sleep_ms(philo->data, philo->data->time_to_eat);
		ft_put_forks_down(philo);
		ft_print_simulation(philo->data, philo->id, "is sleeping");
		ft_sleep_ms(philo->data, philo->data->time_to_sleep);
		ft_print_simulation(philo->data, philo->id, "is thinking");
	}
	return (NULL);
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_simulation(philo->data, philo->id, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		ft_print_simulation(philo->data, philo->id, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_simulation(philo->data, philo->id, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print_simulation(philo->data, philo->id, "has taken right fork");
	}
}

void	ft_put_forks_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_print_simulation(t_data *data, int philo_id, char *message)
{
	long	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	if (!ft_has_ended(data))
	{
		timestamp = ft_get_time_ms() - data->start_time;
		printf("%ld %d %s\n", timestamp, philo_id, message);
	}
	pthread_mutex_unlock(&data->print_mutex);
}
