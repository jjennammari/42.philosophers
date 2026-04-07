/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 14:23:39 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/05 14:25:43 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct s_data
{
	long			start_time;
	bool			end;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;

}	t_data;

typedef struct s_philo
{
	bool			full;
	int				id;
	long			meals_eaten;
	long			time_of_eat;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

/* main.c */
int		main(int ac, char **av);
int		init_data(t_data *data, char **av, int ac);

/* philo_parse.c */
int		parse_input(char **av, int ac);
bool	ft_isdigit(char *str);
size_t	ft_strlen(char *str);
bool	ft_only_zero(char *str);
bool	ft_confirm_bigger_maxint(char *str);

#endif
