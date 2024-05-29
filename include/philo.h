/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:34:59 by asamuilk          #+#    #+#             */
/*   Updated: 2024/02/05 17:45:42 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define THINK "is thinking"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define LEAVE "has left the table"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				is_taken;
}	t_fork;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_leave;
	int				max_eat_count;
	int				time_left;
	int				eat_count;
	pthread_mutex_t	*output_mutex;
	pthread_mutex_t	*stop_mutex;
	int				*stop;
}	t_philosopher;

typedef struct s_vars
{
	t_philosopher	*philosophers;
	t_fork			*forks;
	int				num_ph;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_leave;
	int				max_eat_count;
	pthread_mutex_t	output_mutex;
	pthread_mutex_t	stop_mutex;
	int				stop;
}	t_vars;

int		parse(char **av, t_vars *vars);
void	init(t_vars *vars);
void	print_status(t_philosopher *p, char *status);
void	*philosophize(void *ph);
int		take_forks(t_philosopher *p);
void	put_forks(t_fork *left, t_fork *right);
void	exit_clean(t_vars *vars);

#endif