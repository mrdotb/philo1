/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <bchaleil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 01:06:42 by bchaleil          #+#    #+#             */
/*   Updated: 2020/04/19 01:06:42 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_atoi(const char *str)
{
	int	neg;
	int	r;

	neg = 0;
	r = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		neg = 1;
		str++;
	}
	while (ISDIGIT(*str))
		r = (r * 10) - (*str++ - '0');
	return (neg) ? r : -(r);
}

static size_t		ft_itoa_len(unsigned long n)
{
	size_t	r;

	if (n == 0)
		return (1);
	r = 0;
	while (n)
	{
		n /= 10;
		r++;
	}
	return (r);
}

char				*ft_itoa_long_un(unsigned long n)
{
	size_t	l;
	size_t	e;
	char	*r;

	e = 0;
	l = ft_itoa_len(n);
	if (!(r = (char *)malloc(l + 1)))
		return (NULL);
	r[l] = '\0';
	while (l-- > e)
	{
		r[l] = '0' + n % 10;
		n /= 10;
	}
	return (r);
}
