/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:16:41 by asamuilk          #+#    #+#             */
/*   Updated: 2024/02/05 17:35:17 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_vars *vars)
{
	int				i;

	vars->forks = malloc(sizeof(t_fork) * vars->num_ph);
	if (!vars->forks)
		return ;
	i = 0;
	while (i < vars->num_ph)
	{
		vars->forks[i].is_taken = 0;
		pthread_mutex_init(&vars->forks[i].mutex, NULL);
		i ++;
	}
}

static void	init_philosophers(t_vars *vars)
{
	int				i;

	vars->philosophers = malloc(sizeof(t_philosopher) * vars->num_ph);
	if (!vars->philosophers)
		return ;
	i = 0;
	while (i < vars->num_ph)
	{
		vars->philosophers[i].id = i + 1;
		vars->philosophers[i].left_fork = &vars->forks[i];
		vars->philosophers[i].right_fork = &vars->forks[(i + 1) % vars->num_ph];
		vars->philosophers[i].time_to_eat = vars->time_to_eat;
		vars->philosophers[i].time_to_sleep = vars->time_to_sleep;
		vars->philosophers[i].time_to_leave = vars->time_to_leave;
		vars->philosophers[i].max_eat_count = vars->max_eat_count;
		vars->philosophers[i].time_left = vars->time_to_leave;
		vars->philosophers[i].eat_count = 0;
		vars->philosophers[i].stop_mutex = &vars->stop_mutex;
		vars->philosophers[i].stop = &vars->stop;
		vars->philosophers[i].output_mutex = &vars->output_mutex;
		i ++;
	}
}

static void	init_threads(t_vars *vars)
{
	int				i;

	i = 0;
	while (i < vars->num_ph)
	{
		pthread_create(&vars->philosophers[i].thread, NULL, \
						philosophize, &vars->philosophers[i]);
		i ++;
	}
	if (!vars->max_eat_count)
	{
		i = 0;
		while (i < vars->num_ph)
			pthread_detach(vars->philosophers[i++].thread);
		while (!vars->stop)
			continue ;
	}
	else
	{
		i = 0;
		while (i < vars->num_ph)
			pthread_join(vars->philosophers[i++].thread, NULL);
	}
}

void	init(t_vars *vars)
{
	vars->stop = 0;
	init_forks(vars);
	init_philosophers(vars);
	pthread_mutex_init(&vars->stop_mutex, NULL);
	pthread_mutex_init(&vars->output_mutex, NULL);
	init_threads(vars);
}
