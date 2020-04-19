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

/* static void print(t_philo *philo, char* action, char* color) */
/* { */
/* 	static struct timeval 	start = {.tv_sec = 0, .tv_usec = 0}; */
/* 	struct timeval 			now; */
/* 	unsigned long 			time; */
/* 	char					*time_str; */
/* 	char					*thread_nb_str; */
/* 	char					*final_str; */
/* 	int						i; */
/* 	int						j; */

/* 	i = 0; */
/* 	if (start.tv_sec == 0) */
/* 		if (gettimeofday(&start, NULL) != 0) */
/* 			return ; */
/* 	if (gettimeofday(&now, NULL) != 0) */
/* 		return ; */
/* 	time = time_diff(&now, &start); */
/* 	time_str = ft_itoa_long_un(time); */
/* 	thread_nb_str = ft_itoa_long_un(philo->thread_nb); */
/* 	final_str = malloc(sizeof(char) * (ft_strlen(color) + ft_strlen(time_str) + ft_strlen(thread_nb_str) + ft_strlen(action) + ft_strlen(RESET) + 20) + 1); */
/* 	j = 0; */
/* 	while (color[j]) */
/* 		final_str[i++] = color[j++]; */
/* 	j = 0; */
/* 	while (time_str[j]) */
/* 		final_str[i++] = time_str[j++]; */
/* 	final_str[i++] = ' '; */
/* 	j = 0; */
/* 	while (thread_nb_str[j]) */
/* 		final_str[i++] = thread_nb_str[j++]; */
/* 	final_str[i++] = ' '; */
/* 	j = 0; */
/* 	while (action[j]) */
/* 		final_str[i++] = action[j++]; */
/* 	final_str[i++] = '\n'; */
/* 	j = 0; */
/* 	while (action[j]) */
/* 		final_str[i++] = RESET[j++]; */
/* 	final_str[i] = '\0'; */
/* 	ft_putstr_fd(final_str, 1); */
/* 	free(time_str); */
/* 	free(thread_nb_str); */
/* 	free(final_str); */
/* 	/1* printf("%ld %d %s\n", time, philo->thread_nb, action); *1/ */
/* } */

void	*thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	while (1)
	{
		log_status(philo, THINKING);
		pthread_mutex_lock(&philo->left_fork);
		log_status(philo, L_FORK);
		pthread_mutex_lock(&philo->right_fork);
		log_status(philo, R_FORK);
		log_status(philo, EATING);
		usleep(philo->args->time_to_eat * MSEC);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		if (gettimeofday(&(philo->last_meal), NULL) != 0)
			return (NULL);
		philo->meals++;
		log_status(philo, SLEEPING);
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
			log_status(philos[i], DEAD);
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
