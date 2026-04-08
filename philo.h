/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 14:23:39 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/07 20:10:26 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_philo
{
	bool			full;
	int				id;
	long			meals_eaten;
	long			time_of_eat;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	long			start_time;
	long			philo_amount;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	bool			end;
	pthread_mutex_t	*forks;
	t_philo			*philos;

}	t_data;

/* main.c */
int		main(int ac, char **av);

/* parse.c */
int		ft_parse_input(char **av, int ac);
bool	ft_not_digit(char *str);
bool	ft_wrong_value(char *str);
bool	ft_confirm_bigger_maxint(char *str);

/* init_variables.c */
int		ft_init_variables(t_data *data, char **av, int ac);
void	ft_convert_av(t_data *data, char **av, int ac);
long	ft_atol(char *str);
int		ft_data_init(t_data *data);
int		ft_philo_init(t_data *data);//TODO: change to void function?

/* run_simulation.c */
int		ft_start_simulation(t_data *data);
long	ft_get_time(t_data *data);

#endif
