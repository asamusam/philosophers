/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:13:32 by asamuilk          #+#    #+#             */
/*   Updated: 2024/02/05 17:48:28 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks(t_fork *right, t_fork *left)
{
	pthread_mutex_lock(&right->mutex);
	right->is_taken = 0;
	pthread_mutex_unlock(&right->mutex);
	pthread_mutex_lock(&left->mutex);
	left->is_taken = 0;
	pthread_mutex_unlock(&left->mutex);
}

static int	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (!fork->is_taken)
	{
		fork->is_taken = 1;
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

int	take_forks(t_philosopher *p)
{
	while (!take_fork(p->left_fork))
	{
		usleep(1000);
		p->time_left -= 1;
		if (!p->time_left)
			return (0);
	}
	print_status(p, FORK);
	while (!take_fork(p->right_fork))
	{
		usleep(1000);
		p->time_left -= 1;
		if (!p->time_left)
			return (0);
	}
	print_status(p, FORK);
	return (1);
}
