/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:59:04 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/05 18:30:11 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse_input(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_not_digit(av[i]))
			return (printf("Error: use only digits in the input"), -1);
		else if (ft_wrong_value(av[i]))
			return (printf("Error: use only values bigger than 0 and\
				smaller or equal to max int"), -1);
		i++;
	}
	return (0);
}

bool	ft_not_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

bool	ft_wrong_value(char *str)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (1);
	start = i;
	count = 0;
	while (str[i])
	{
		count++;
		i++;
	}
	if (count > 10 || (count == 10 && ft_confirm_bigger_maxint(&str[start])))
		return (1);
	return (0);
}

bool	ft_confirm_bigger_maxint(char *str)
{
	const char	*max_int;
	int		i;

	max_int = "2147483647";
	i = 0;
	while (str[i])
	{
		if (str[i] > max_int[i])
			return (1);
		i++;
	}
	return (0);
}
