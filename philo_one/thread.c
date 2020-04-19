/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <bchaleil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 19:43:39 by bchaleil          #+#    #+#             */
/*   Updated: 2020/04/18 19:43:39 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Returns a int
** 0 for success
** 1 for malloc error
** 2 for mutex error
** 3 for usleep error
** 4 for timeofday error
*/

static int	thread_start_ex(t_philo **philo)
{
	if (log_status(*philo, THINKING) != 0)
		return (1);
	if (pthread_mutex_lock(&((*philo)->left_fork)) != 0)
		return (2);
	if (log_status(*philo, L_FORK) != 0)
		return (1);
	if (pthread_mutex_lock(&((*philo)->right_fork)) != 0)
		return (2);
	if (log_status(*philo, R_FORK) != 0)
		return (1);
	if (log_status(*philo, EATING) != 0)
		return (1);
	if (usleep((*philo)->args->time_to_eat * MSEC) != 0)
		return (3);
	if (pthread_mutex_unlock(&((*philo)->left_fork)) != 0 ||
			pthread_mutex_unlock(&((*philo)->right_fork)) != 0)
		return (2);
	if (gettimeofday(&((*philo)->last_meal), NULL) != 0)
		return (4);
	(*philo)->meals++;
	if (log_status(*philo, SLEEPING) != 0)
		return (1);
	if (usleep((*philo)->args->time_to_sleep * MSEC) != 0)
		return (3);
	return (0);
}

/*
** Returns a pointer
** 0 for success
** 1 or NULL for malloc error
** 2 for mutex error
** 3 for usleep error
** 4 for timeofday error
*/

void		*thread_start(void *arg)
{
	t_philo			*philo;
	int				*ret;
	int				r;

	philo = (t_philo*)arg;
	if ((ret = malloc(sizeof(int))) == NULL)
		return (NULL);
	ret[0] = 0;
	while (1)
	{
		r = thread_start_ex(&philo);
		if (r > 0)
		{
			ret[0] = r;
			return (ret);
		}
		if (philo->args->must_eat > 0 && philo->meals > philo->args->must_eat)
			return (ret);
	}
}

static int	death_thread_ex(t_philo **philos, struct timeval *now, t_args *args)
{
	unsigned int i;
	unsigned long all_meals;

	i = 0;
	all_meals = 0;
	while (i < args->number_of_philosopher)
	{
		if (time_diff(now, &philos[i]->last_meal) > args->time_to_die)
		{
			log_status(philos[i], DEAD);
			return (1);
		}
		if (args->must_eat != 0)
		{
			all_meals += philos[i]->meals;
			if (all_meals == (args->must_eat * args->number_of_philosopher))
				return (0);
		}
		i++;
	}
	return (2);
}

void		*death_thread(void *arg)
{
	t_philo			**philos;
	t_args			*args;
	struct timeval	now;
	int				*ret;
	int				r;

	if ((ret = malloc(sizeof(int))) == NULL)
		return (NULL);
	philos = arg;
	args = philos[0]->args;
	while (1)
	{
		usleep(10 * MSEC);
		if (gettimeofday(&now, NULL) != 0)
			return (NULL);
		r = death_thread_ex(philos, &now, args);
		if (r == 0 || r == 1)
		{
			ret[0] = r;
			return (ret);
		}
	}
}
