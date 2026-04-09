/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:00:02 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/09 14:05:05 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg);
void	ft_one_philo(t_philo *philo);
void	ft_take_forks(t_philo *philo);
void	ft_put_forks_down(t_philo *philo);
void	ft_print_simulation(t_data *data, int philo_id, char *message);

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_amount == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	if (philo->data->philo_amount % 2 == 0 && philo->id % 2 == 0)
		usleep(1000);
	else if (philo->data->philo_amount % 2 != 0)
	{
		if (philo->id == philo->data->philo_amount)
			ft_sleep_ms(philo->data, philo->data->time_to_eat * 2 - 1);
		else if (philo->id % 2 == 0)
			ft_sleep_ms(philo->data, philo->data->time_to_eat - 1);
	}
	while (!ft_has_ended(philo->data))
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		pthread_mutex_unlock(&philo->data->meal_mutex);
		// only take the forks when they are close to death
		ft_take_forks(philo);
		philo->last_meal_ms = ft_get_time_ms();
		ft_print_simulation(philo->data, philo->id, "is eating");
		ft_sleep_ms(philo->data, philo->data->time_to_eat);
		ft_put_forks_down(philo);
		philo->meals_eaten++;
		ft_print_simulation(philo->data, philo->id, "is sleeping");
		ft_sleep_ms(philo->data, philo->data->time_to_sleep);
		ft_print_simulation(philo->data, philo->id, "is thinking");
		while (ft_get_time_ms() - (philo->last_meal_ms + philo->data->time_to_die - 2))
			usleep(100);
	}
	return (NULL);
}

void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_simulation(philo->data, philo->id, "has taken a fork");
	while (!ft_has_ended(philo->data))
		usleep(1000);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->order_mutex);
	// if (philo->id % 2 == 0)
	// {
	pthread_mutex_lock(philo->right_fork);
	ft_print_simulation(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	ft_print_simulation(philo->data, philo->id, "has taken a fork");
	// }
	// else
	// {
	// 	pthread_mutex_lock(philo->left_fork);
	// 	ft_print_simulation(philo->data, philo->id, "has taken a fork");
	// 	pthread_mutex_lock(philo->right_fork);
	// 	ft_print_simulation(philo->data, philo->id, "has taken a fork");
	// }
	pthread_mutex_unlock(&philo->data->order_mutex);
}

void	ft_put_forks_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_print_simulation(t_data *data, int philo_id, char *message)
{
	long	timestamp;

	pthread_mutex_lock(&data->end_mutex);
	if (!data->end_simulation)
	{
		pthread_mutex_lock(&data->print_mutex);
		timestamp = ft_get_time_ms() - data->start_time;
		printf("%ld %d %s\n", timestamp, philo_id, message);
		pthread_mutex_unlock(&data->print_mutex);
	}
	pthread_mutex_unlock(&data->end_mutex);
}
