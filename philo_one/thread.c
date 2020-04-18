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

static unsigned long	time_diff(struct timeval *t1, struct timeval *t2)
{
	unsigned long diff;

	diff = (t1->tv_sec - t2->tv_sec) * 1000;
	diff += (t1->tv_usec - t2->tv_usec) / 1000;
	return (diff);
}

static void print(t_philo *philo, char* action)
{
	static struct timeval 	start = {.tv_sec = 0, .tv_usec = 0};
	struct timeval 			now;
	unsigned long 			time;

	if (start.tv_sec == 0)
		if (gettimeofday(&start, NULL) != 0)
			return ;

	if (gettimeofday(&now, NULL) != 0)
		return ;
	time = time_diff(&now, &start);
	/* printf("%ld %d %s\n", time, philo->thread_nb, action); */
}

void	*thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	while (1)
	{
		print(philo, "is thinking");
		pthread_mutex_lock(&philo->left_fork);
		print(philo, "has taken left fork");
		pthread_mutex_lock(&philo->right_fork);
		print(philo, "has taken right fork");;
		print(philo, "is eating");
		usleep(philo->args->time_to_eat * MSEC);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		if (gettimeofday(&(philo->last_meal), NULL) != 0)
			return (NULL);
		philo->meals++;
		print(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * MSEC);
		if (philo->args->must_eat > 0
				&& philo->meals > philo->args->must_eat)
			return (NULL);
	}
}
static int	death_thread_ex(t_philo **philos, struct timeval *now, t_args *args)
{
	unsigned int i;
	unsigned int all_meals;

	i = 0;
	all_meals = 0;
	while (i < args->number_of_philosopher)
	{
		/* printf("time_diff: %ld time_to_die: %d\n", time_diff(now, &philos[i]->last_meal), args->time_to_die); */
		if (time_diff(now, &philos[i]->last_meal) > args->time_to_die)
		{
			print(philos[i], "is dead");
			return (1);
		}
		if (args->must_eat != 0)
		{
			all_meals += philos[i]->meals;
			/* printf("%d == %d\n", all_meals, (args->must_eat * args->number_of_philosopher)); */
			if (all_meals == (args->must_eat * args->number_of_philosopher)) {
				return (0);
			}
		}
		i++;
	}
	return (2);
}

void	*death_thread(void *arg)
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
