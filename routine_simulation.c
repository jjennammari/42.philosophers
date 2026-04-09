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
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!ft_has_ended(philo->data))
	{
		ft_take_forks(philo);
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->last_meal_ms = ft_get_time_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		ft_print_simulation(philo->data, philo->id, "is eating");
		ft_sleep_ms(philo->data, philo->data->time_to_eat);
		ft_put_forks_down(philo);
		ft_print_simulation(philo->data, philo->id, "is sleeping");
		ft_sleep_ms(philo->data, philo->data->time_to_sleep);
		ft_print_simulation(philo->data, philo->id, "is thinking");
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
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	if (first == philo->left_fork)
		ft_print_simulation(philo->data, philo->id, "has taken a fork");
	else
		ft_print_simulation(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(second);
	if (second == philo->left_fork)
		ft_print_simulation(philo->data, philo->id, "has taken a fork");
	else
		ft_print_simulation(philo->data, philo->id, "has taken a fork");
}

void	ft_put_forks_down(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
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
