/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <bchaleil@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 23:34:43 by bchaleil          #+#    #+#             */
/*   Updated: 2020/04/19 23:34:43 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static char	*get_msg(t_msg action)
{
	static char	*msgs[] = {

	"is dead", "is thinking",
	"has taken left fork", "has taken right fork",
	"is eating", "is sleeping"};
	return (msgs[action]);
}

static char	*get_color(t_msg action)
{
	static char	*msg_colors[] = {

	RED, GREEN,
	YELLOW, YELLOW,
	BLUE, CYAN};
	return (msg_colors[action]);
}

static void	log_fill(char **msg, t_msg action, char *time_str, char *thread_nb)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (get_color(action)[j])
		(*msg)[i++] = get_color(action)[j++];
	j = 0;
	while (time_str[j])
		(*msg)[i++] = time_str[j++];
	(*msg)[i++] = ' ';
	j = 0;
	while (thread_nb[j])
		(*msg)[i++] = thread_nb[j++];
	(*msg)[i++] = ' ';
	j = 0;
	while (get_msg(action)[j])
		(*msg)[i++] = get_msg(action)[j++];
	j = 0;
	while (RESET[j])
		(*msg)[i++] = RESET[j++];
	(*msg)[i++] = '\n';
	(*msg)[i] = '\0';
}

static char	*log_alloc(char *time_str, char *thread_nb, char *msg)
{
	int		len;
	char	*alloc;

	len = ft_strlen(time_str) + ft_strlen(thread_nb) + ft_strlen(msg);
	len += C_SIZE + 4;
	alloc = malloc(len * sizeof(char) + 1);
	if (alloc == NULL)
		return (NULL);
	return (alloc);
}

int			log_status(t_philo *philo, t_msg action)
{
	static struct timeval	start = {.tv_sec = 0, .tv_usec = 0};
	struct timeval			now;
	char					*time_str;
	char					*msg;

	if (start.tv_sec == 0)
		if (gettimeofday(&start, NULL) != 0)
			return (1);
	if (gettimeofday(&now, NULL) != 0)
		return (1);
	if ((time_str = ft_itoa_long_un(time_diff(&now, &start))) == NULL)
		return (1);
	msg = log_alloc(time_str, philo->thread_nb, get_msg(action));
	if (msg == NULL)
		return (1);
	log_fill(&msg, action, time_str, philo->thread_nb);
	ft_putstr_fd(msg, 1);
	free(time_str);
	free(msg);
	return (0);
}
