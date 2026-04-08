/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:43:53 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/07 14:45:56 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_variables(t_data *data, char **av, int ac)
{
	ft_convert_av(data, av, ac);
	if (ft_data_init(data) != 0)
		return (-1);
	if (ft_philo_init(data) != 0)
		return (-1);
	return (0);
}

void	ft_convert_av(t_data *data, char **av, int ac)
{
	data->philo_amount = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) * 1000;
	data->time_to_eat = ft_atol(av[3]) * 1000;
	data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (ac == 6 && av[5])
		data->max_meals = ft_atol(av[5]);
	else
		data->max_meals = -1;
}

long	ft_atol(char *str)
{
	long	nb;
	int		i;

	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	ft_data_init(t_data *data)
{
	long	i;

	data->start_time = 0;
	data->end = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_amount);
	if (!data->forks)
		return (printf("Error: malloc failed"), -1);
	data->philos = malloc(sizeof(t_philo) * data->philo_amount);
	if (!data->philos)
		return (printf("Error: malloc failed"), -1);
	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Error: mutex init failed"), -1);
		i++;
	}
	return (0);
}

int	ft_philo_init(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->philo_amount)
	{
		data->philos[i].full = 0;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].time_of_eat = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_amount];
		i++;
	}
	return (0);
}
