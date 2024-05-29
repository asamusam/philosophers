/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:09:07 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/29 18:45:22 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	get_current_time(void)
{
	struct timeval	time;
	long int		res;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

void	print_status(t_philosopher *p, char *status)
{
	pthread_mutex_lock(p->output_mutex);
	printf("%ld %d %s\n", get_current_time(), p->id, status);
	pthread_mutex_unlock(p->output_mutex);
}

void	exit_clean(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_ph)
		pthread_mutex_destroy(&vars->forks[i++].mutex);
	pthread_mutex_destroy(&vars->stop_mutex);
	pthread_mutex_destroy(&vars->output_mutex);
	free(vars->forks);
	free(vars->philosophers);
}
