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
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal_ms;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long			start_time;
	long			philo_amount;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	bool			end_simulation;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	order_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;

}	t_data;

/* main.c */
int		main(int ac, char **av);

/* parse_input.c */
int		ft_parse_input(char **av, int ac);
bool	ft_not_digit(char *str);
bool	ft_wrong_value(char *str);
bool	ft_confirm_bigger_maxint(char *str);

/* init_variables.c */
int		ft_init_variables(t_data *data, char **av, int ac);
void	ft_convert_av(t_data *data, char **av, int ac);
long	ft_atol(char *str);
int		ft_data_init(t_data *data);
void	ft_philo_init(t_data *data);

/* run_simulation.c */
int		ft_run_simulation(t_data *data);
void	ft_init_last_meals(t_data *data);
int		ft_create_threads(t_data *data, long *created);
void	ft_join_threads(t_data *data, long created);
void	ft_sleep_ms(t_data *data, long time_ms);

/* routine_simulation.c */
void	*ft_routine(void *arg);
void	ft_one_philo(t_philo *philo);
void	ft_take_forks(t_philo *philo);
void	ft_put_forks_down(t_philo *philo);
void	ft_print_simulation(t_data *data, int philo_id, char *message);

/* monitor_simulation.c */
void	ft_monitor(t_data *data);
int		ft_check_full(t_data *data);
int		ft_check_death(t_data *data);
int		ft_end_print_death(t_data *data, long i);
long	ft_get_time_ms(void);

/* end_simulation.c */
void	ft_clear_data(t_data *data);
bool	ft_has_ended(t_data *data);
void	ft_set_end(t_data *data, bool value);

#endif
