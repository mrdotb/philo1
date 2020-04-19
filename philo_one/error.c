/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <bchaleil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 21:41:45 by bchaleil          #+#    #+#             */
/*   Updated: 2020/04/19 21:41:45 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	pthread_error(void)
{
	static char error_str[] =

	RED"pthread error\n"RESET;
	ft_putstr_fd(error_str, 2);
	return (1);

}

int	malloc_error(void)
{
	static char error_str[] =

	RED"malloc error\n"RESET;
	ft_putstr_fd(error_str, 2);
	return (1);
}

