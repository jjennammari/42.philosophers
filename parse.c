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

int	parse_input(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if(ft_strlen(av[i]) > 10)
			return (1);
		else if (ft_isdigit(av[i]))
			return (1);
		else if (ft_only_zero(av[i]))
			return (1);
		else if (ft_strlen(av[i]) == 10 && ft_confirm_bigger_maxint(av[i]))
			return (1);
		i++;
	}
	return (0);
}

bool	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (11);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	ft_only_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '\0')
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
