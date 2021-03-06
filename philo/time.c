/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:38:32 by ncathy            #+#    #+#             */
/*   Updated: 2022/06/27 11:15:52 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	long			current_time;
	struct timeval	t_time;

	gettimeofday(&t_time, 0);
	current_time = t_time.tv_sec * 1000 + t_time.tv_usec / 1000;
	return (current_time);
}

int	ft_usleep(long mseconds)
{
	long	before;
	long	after;

	before = get_time();
	after = before;
	while (after - before < mseconds)
	{
		if (usleep(mseconds) == -1)
			return (-1);
		after = get_time();
	}
	return (0);
}

int	is_philo_going_to_die(t_philo_struct *ph, int i)
{
	pthread_mutex_lock(&ph->ate_last_time_lock);
	if (get_time() - ph->each_philo[i].ate_last_time >= ph->time_to_die)
	{
		pthread_mutex_unlock(&ph->ate_last_time_lock);
		return (1);
	}
	pthread_mutex_unlock(&ph->ate_last_time_lock);
	return (0);
}
