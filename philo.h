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
	
} t_data;

typedef struct s_philo
{
	uint64_t	meal_count;
	uint64_t	time_of_eat;
} t_philo;

/* main.c */
void	init_variables();
void	print_error(char *str);

/* philo_parse.c */
int	parse_philo(char **av);

#endif
