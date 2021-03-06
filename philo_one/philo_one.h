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

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define C_SIZE  16
# define RESET   "\x1b[0m"

# define ISDIGIT(c) (c >= '0' && c <= '9')

typedef enum		e_msg
{
	DEAD = 0,
	THINKING = 1,
	L_FORK = 2,
	R_FORK = 3,
	EATING = 4,
	SLEEPING = 5,
}					t_msg;

typedef struct		s_args
{
	unsigned int	number_of_philosopher;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat;
}					t_args;

typedef struct		s_philo
{
	pthread_t		thread_id;
	char			*thread_nb;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	unsigned int	meals;
	struct timeval	last_meal;
	t_args			*args;
}					t_philo;

size_t				ft_strlen(const char *str);
int					ft_atoi(const char *str);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_itoa_long_un(unsigned long n);
t_philo				**create_philos(t_args *args);
int					free_philos(t_philo **philos, t_args *args);
void				*thread_start(void	*arg);
void				*death_thread(void *arg);
int					pthread_error(void);
int					malloc_error(void);
unsigned long		time_diff(struct timeval *t1, struct timeval *t2);
int					log_status(t_philo *philo, t_msg action);

#endif
