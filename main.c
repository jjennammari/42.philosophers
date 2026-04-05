/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemustaj <jemustaj@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:49:41 by jemustaj          #+#    #+#             */
/*   Updated: 2026/04/05 18:53:58 by jemustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_variables();
void	print_error(char *str);

int	main(int ac, char **av)
{
	if (ac == 5  || ac == 6)
	{
		parse_philo(av);
	}
	else
		return (print_error("Execute program with 5 or 6 arguments"), 1);
	return (0);
}

void	print_error(char *str)
{
	printf("%s\n", str);
}
