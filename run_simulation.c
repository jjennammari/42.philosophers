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

int	ft_run_simulation(t_data *data)
{
	data->start_time = ft_get_time_ms();
	ft_init_last_meals(data);
	if (ft_create_threads(data) != 0)
		return (printf("Error: thread creation failed"), -1);
	ft_monitor(data);
	ft_join_threads(data);
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

int	ft_create_threads(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, ft_routine, &data->philos[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_join_threads(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->philo_amount)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

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
	if (philo->data->philo_amount == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
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
	ft_print_simulation(philo->data, philo->id, "has taken left fork");
	ft_sleep_ms(philo->data, philo->data->time_to_die);
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
		ft_print_simulation(philo->data, philo->id, "has taken left fork");
	else
		ft_print_simulation(philo->data, philo->id, "has taken right fork");
	pthread_mutex_lock(second);
	if (second == philo->left_fork)
		ft_print_simulation(philo->data, philo->id, "has taken left fork");
	else
		ft_print_simulation(philo->data, philo->id, "has taken right fork");
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
		pthread_mutex_lock(&data->meal_mutex);
		meals = data->philos[i].meals_eaten;
		pthread_mutex_unlock(&data->meal_mutex);
		if (meals >= data->max_meals)
			full_count++;
		i++;
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
		pthread_mutex_lock(&data->meal_mutex);
		last = data->philos[i].last_meal_ms;
		pthread_mutex_unlock(&data->meal_mutex);
		if (now - last >= data->time_to_die)
			return (ft_end_print_death(data, i));
		i++;
	}
	return (0);
}

int	ft_end_print_death(t_data *data, long i)
{
	long	now;
	int		ended;

	pthread_mutex_lock(&data->end_mutex);
	ended = data->end_simulation;
	if (!ended)
		data->end_simulation = 1;
	pthread_mutex_unlock(&data->end_mutex);
	if (ended)
		return (1);
	now = ft_get_time_ms();
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n", now - data->start_time, data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
	return (1);
}
