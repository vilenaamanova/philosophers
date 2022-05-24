/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:38:32 by ncathy            #+#    #+#             */
/*   Updated: 2022/05/23 19:38:52 by ncathy           ###   ########.fr       */
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
