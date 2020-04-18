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

int	usage(void)
{
	ft_putstr_fd("philo_one\n", 2);
	ft_putstr_fd("Usage:\n", 2);
	ft_putstr_fd("philo_one number_of_philosopher time_to_die time_to_eat", 2);
	ft_putstr_fd(" time_to_sleep", 2);
	ft_putstr_fd(" [number_of_time_each_philosophers_must_eat]\n", 2);
	return (1);
}

int	parse_arg(t_args *args, int argc, char **argv)
{
	static int	i = 1;
	static int	args_tab[5] = {0, 0, 0, 0, 0};

	if (argc < 5 || argc > 6)
		return (usage());
	while (i < argc)
	{
		args_tab[i - 1] = ft_atoi(argv[i]);
		if (args_tab[i - 1] < 1)
			return (usage());
		i++;
	}
	args->number_of_philosopher = args_tab[0];
	args->time_to_die = args_tab[1];
	args->time_to_eat = args_tab[2];
	args->time_to_sleep = args_tab[3];
	args->must_eat = args_tab[4];
	return (0);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo			**philos;
	pthread_t		death_thread_id;
	unsigned int	i;
	int				*death_result;

	if (parse_arg(&args, argc, argv) == 1)
		return (1);
	if ((philos = create_philos(&args)) == NULL)
		return (1);
	i = 0;
	while (i < args.number_of_philosopher)
	{
		pthread_create(&philos[i]->thread_id, NULL, &thread_start, philos[i]);
		i++;
	}
	pthread_create(&death_thread_id, NULL, &death_thread, philos);
	pthread_join(death_thread_id, (void**)&death_result);
	/* printf("pthread death_join death_result%d\n", *death_result); */
	if (death_result == NULL)
		return 1;
	if (*death_result == 1)
	{
		free_philos(philos, &args);
		free(death_result);
		return 0;
	}
	free(death_result);
	i = 0;
	while (i < args.number_of_philosopher)
	{
		pthread_join(philos[i]->thread_id, NULL);
		printf("pthread_join %d\n", i);
		i++;
	}
	if (free_philos(philos, &args) == 1)
		return (1);
	return (0);
}
