/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <bchaleil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 17:34:50 by bchaleil          #+#    #+#             */
/*   Updated: 2020/04/18 17:34:50 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static t_philo	**create_philos_ex(t_args *args)
{
	t_philo			**philos;
	unsigned int	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->number_of_philosopher);
	if (philos == NULL)
		return (NULL);
	while (i < args->number_of_philosopher)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (NULL);
		if ((philos[i]->thread_nb = ft_itoa_long_un(i + 1)) == NULL)
			return (NULL);
		philos[i]->meals = 0;
		philos[i]->args = args;
		if (gettimeofday(&(philos[i]->last_meal), NULL) != 0)
			return (NULL);
		i++;
	}
	return (philos);
}

int				free_philos(t_philo **philos, t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->number_of_philosopher - 1)
	{
		if (i == 0)
			if (pthread_mutex_destroy(&philos[i]->left_fork) != 0)
				return (1);
		if (pthread_mutex_destroy(&philos[i]->right_fork) != 0)
			return (1);
		free(philos[i]);
		i++;
	}
	free(philos[i]);
	free(philos);
	return (0);
}

t_philo			**create_philos(t_args *args)
{
	static unsigned int	i = 0;
	t_philo				**philos;

	if ((philos = create_philos_ex(args)) == NULL)
		return (NULL);
	while (i < args->number_of_philosopher)
	{
		if (i == 0)
		{
			if (pthread_mutex_init(&philos[i]->left_fork, NULL) != 0
					|| pthread_mutex_init(&philos[i]->right_fork, NULL) != 0)
				return (NULL);
		}
		else if (i == args->number_of_philosopher)
		{
			philos[i]->left_fork = philos[i - 1]->right_fork;
			philos[i]->right_fork = philos[0]->left_fork;
		}
		else
		{
			philos[i]->left_fork = philos[i - 1]->right_fork;
			if (pthread_mutex_init(&philos[i]->right_fork, NULL) != 0)
				return (NULL);
		}
		i++;
	}
	return (philos);
}
