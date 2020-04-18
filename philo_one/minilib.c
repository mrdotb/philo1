/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <bchaleil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 14:16:08 by bchaleil          #+#    #+#             */
/*   Updated: 2020/04/18 14:16:08 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

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

static char		*ft_itoa_recurse(int n, int size, char *nbr)
{
	if (n < 0)
	{
		nbr[0] = '-';
		return (ft_itoa_recurse(n * -1, size, nbr));
	}
	if (n >= 10 && size >= 0)
	{
		nbr[size] = (n % 10) + '0';
		return (ft_itoa_recurse(n / 10, size - 1, nbr));
	}
	nbr[size] = n + '0';
	return (nbr);
}

static int		ft_numlen(int n)
{
	if (n < 0)
		return (ft_numlen(n * -1) + 1);
	if (n >= 10)
		return (ft_numlen(n / 10) + 1);
	return (1);
}

char			*ft_itoa(int n)
{
	char	*nbr;
	int		size;

	size = ft_numlen(n);
	nbr = malloc(size * sizeof(char) + 1);
	if (nbr == NULL)
		return (NULL);
	return (ft_itoa_recurse(n, size - 1, nbr));
}
