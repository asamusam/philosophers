/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:23:24 by asamuilk          #+#    #+#             */
/*   Updated: 2024/02/05 17:22:54 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi_mod(char *str)
{
	int		result;

	result = 0;
	while (*str <= ' ')
		str ++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (result);
		str ++;
	}
	while ('0' <= *str && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str ++;
	}
	return (result);
}

int	parse(char **av, t_vars *vars)
{
	vars->num_ph = ft_atoi_mod(av[1]);
	vars->time_to_leave = ft_atoi_mod(av[2]);
	vars->time_to_eat = ft_atoi_mod(av[3]);
	vars->time_to_sleep = ft_atoi_mod(av[4]);
	if (!vars->time_to_leave || !vars->time_to_eat || \
		!vars->time_to_sleep || !vars->num_ph)
	{
		printf("Error! All arguments must be greater than 0\n");
		return (0);
	}
	if (av[5])
	{
		vars->max_eat_count = ft_atoi_mod(av[5]);
		if (!vars->max_eat_count)
		{
			printf("Error! All arguments must be greater than 0\n");
			return (0);
		}
	}
	else
		vars->max_eat_count = 0;
	return (1);
}
