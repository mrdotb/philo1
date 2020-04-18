/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <bchaleil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 17:15:58 by bchaleil          #+#    #+#             */
/*   Updated: 2020/04/17 17:15:58 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


static void print(t_philo *philo, char* action)
{
	static struct timeval	start;
	struct timeval 			tv;

	if (gettimeofday(&tv, NULL) == 0)
		printf("%ld.%06ld %d %s\n", tv.tv_sec, tv.tv_usec, philo->thread_nb, action);
}

static void	*thread_start(void *arg)
{
	t_philo	*philo;
	/* struct timeval tv; */
	philo = (t_philo*)arg;
	while (philo->meals < MUST_EAT)
	{
		pthread_mutex_lock(&philo->left_fork);
		print(philo, "has taken left fork");
		pthread_mutex_lock(&philo->right_fork);
		print(philo, "has taken right fork");;
		print(philo, "is eating");
		usleep(TIME_TO_EAT * MSEC);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		/* if (gettimeofday(&tv, NULL) != 0) */
			/* return NULL; */
		/* printf("last meal: %ldsec %dmilli %dsec now - last meal = %ld\n", philo.last_meal.tv_sec, TIME_TO_DIE, TIME_TO_DIE / 1000, tv.tv_sec - philo.last_meal.tv_sec); */
		if (gettimeofday(&(philo->last_meal), NULL) != 0)
			return NULL;
		/* printf("%d last meal %ld\n", philo->thread_nb, philo->last_meal.tv_sec); */
		/* philo->last_meal.tv_sec = tv.tv_sec; */
		/* philo->last_meal.tv_usec = tv.tv_usec; */
		philo->meals++;
		print(philo, "is sleeping");
		usleep(TIME_TO_SLEEP * MSEC);
		print(philo, "is thinking");
	}
	return NULL;
}

void	*death_check(t_philo *philos)
{

	printf("death_check philos is at address: %p\n", (void*)&philos);
	int i;
	struct timeval tv;

	while (1)
	{
		if (gettimeofday(&tv, NULL) != 0)
			return (NULL);
		usleep(10 * MSEC);
		i = 0;
		while (i < NB_PHILO)
		{
			if (tv.tv_sec - (philos)[i].last_meal.tv_sec > TIME_TO_DIE / 1000)
			{
				printf("last meal: %ldsec now: %ldsec %dsec now - last meal = %ld\n", (philos)[i].last_meal.tv_sec, tv.tv_sec, TIME_TO_DIE / 1000, tv.tv_sec - (philos[i]).last_meal.tv_sec);
				print(&(philos)[i], "is dead");
				exit(1);
			}
			i++;
		}
	}
	return NULL;
}

int	main(void)
{
	t_philo		philos[NB_PHILO];
	int					i;

	printf("main philos is at address: %p\n", (void*)&philos);
	i = 0;
	while (i < NB_PHILO)
	{
		philos[i].thread_nb = i + 1;
		/* philos[i].state = THINK; */
		philos[i].meals = 0;
		if (gettimeofday(&philos[i].last_meal, NULL) != 0)
			return (1);
		if (i == 0) {
			if (pthread_mutex_init(&philos[i].left_fork, NULL) != 0)
				return(1);
			if (pthread_mutex_init(&philos[i].right_fork, NULL) != 0)
				return(1);
		} else if (i == NB_PHILO){
			philos[i].left_fork = philos[i - 1].right_fork;
			philos[i].right_fork = philos[0].left_fork;
		} else {
			philos[i].left_fork = philos[i - 1].right_fork;
			if (pthread_mutex_init(&philos[i].right_fork, NULL) != 0)
				return(1);
		}

		pthread_create(&philos[i].thread_id, NULL, &thread_start, &(philos[i]));
		printf("main philo[%d] is at address: %p\n", i, (void*)&philos[i]);
		i++;
	}

	death_check(philos);
	i = 0;
	while (i < NB_PHILO)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}

	i = 0;
	/* while (i < NB_PHILO) */
	/* 	printf("%d last meal %ld\n", philos[i].thread_nb, philos[i].last_meal.tv_sec); */
	/* pthread_mutex_destroy(&lock); */
	return (0);
}
