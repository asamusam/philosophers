/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:40:15 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/29 18:42:01 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	leave(t_philosopher *p)
{
	print_status(p, LEAVE);
	pthread_mutex_lock(p->stop_mutex);
	if (!*p->stop)
		*p->stop = 1;
	pthread_mutex_unlock(p->stop_mutex);
}

static int	nap(t_philosopher *p)
{
	int	sleeping;

	print_status(p, SLEEP);
	sleeping = p->time_to_sleep;
	while (sleeping)
	{
		usleep(1000);
		p->time_left -= 1;
		if (!p->time_left)
			return (0);
		sleeping --;
	}
	return (1);
}

static int	eat(t_philosopher *p)
{
	int	eating;

	print_status(p, EAT);
	p->time_left = p->time_to_leave;
	eating = p->time_to_eat;
	while (eating >= 0)
	{
		usleep(1000);
		p->time_left -= 1;
		if (!p->time_left)
			return (0);
		eating --;
	}
	put_forks(p->right_fork, p->left_fork);
	p->eat_count += 1;
	return (1);
}

void	*philosophize(void *ph)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)ph;
	while (1)
	{
		print_status(philosopher, THINK);
		if (!take_forks(philosopher) || !eat(philosopher))
		{
			leave(philosopher);
			return (0);
		}
		if (philosopher->eat_count == philosopher->max_eat_count)
			return (0);
		if (!nap(philosopher))
		{
			leave(philosopher);
			return (0);
		}
	}
	return (0);
}
