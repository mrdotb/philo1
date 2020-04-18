/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <bchaleil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 16:23:50 by bchaleil          #+#    #+#             */
/*   Updated: 2020/04/17 16:23:50 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>

# define SEC 1000000
# define MSEC 1000
# define NB_PHILO 3
# define TIME_TO_DIE 10000
# define TIME_TO_EAT 1000
# define TIME_TO_SLEEP 1000
# define MUST_EAT 10

typedef struct s_philo
{
	pthread_t		thread_id;
	int				thread_nb;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	int				meals;
	struct timeval	last_meal;
}					t_philo;

#endif
