#include "philo_one.h"

unsigned long	time_diff(struct timeval *t1, struct timeval *t2)
{
	unsigned long diff;

	diff = (t1->tv_sec - t2->tv_sec) * 1000;
	diff += (t1->tv_usec - t2->tv_usec) / 1000;
	return (diff);
}

int				log_status(t_philo *philo, t_msg action)
{
	static struct timeval 	start = {.tv_sec = 0, .tv_usec = 0};
	struct timeval 			now;
	static char				*msgs[] = {
		"is dead", "is thinking",
		"has taken left fork", "has taken right fork",
		"is eating", "is sleeping" };
	static char				*msg_colors[] = { RED, GREEN,
		YELLOW, YELLOW,
		BLUE, CYAN};


	char					*time_str;
	char					*msg;
	int						len;
	int						i;
	int						j;

	if (start.tv_sec == 0)
		if (gettimeofday(&start, NULL) != 0)
			return (1);
	if (gettimeofday(&now, NULL) != 0)
		return (1);
	time_str = ft_itoa_long_un(time_diff(&now, &start));
	len = ft_strlen(time_str) + ft_strlen(philo->thread_nb) +
		ft_strlen(msgs[action]) + C_SIZE + 4;
	msg = malloc(sizeof(char) * len + 1);
	i = 0;
	j = 0;
	while (msg_colors[action][j])
		msg[i++] = msg_colors[action][j++];
	j = 0;
	while (time_str[j])
		msg[i++] = time_str[j++];
	msg[i++] = ' ';
	j = 0;
	while (philo->thread_nb[j])
		msg[i++] = philo->thread_nb[j++];
	msg[i++] = ' ';
	j = 0;
	while (msgs[action][j])
		msg[i++] = msgs[action][j++];
	j = 0;
	while (RESET[j])
		msg[i++] = RESET[j++];
	msg[i++] = '\n';
	msg[i] = '\0';
	ft_putstr_fd(msg, 1);
	free(time_str);
	free(msg);
	return (0);	
}
