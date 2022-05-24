/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:41:42 by ncathy            #+#    #+#             */
/*   Updated: 2022/05/23 20:54:48 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_each_philo *each_philo, t_philo_struct *ph)
{
	pthread_mutex_lock(&ph->forks[each_philo->left]);
	philo_print(each_philo, PHILO_FORK);
	pthread_mutex_lock(&ph->forks[each_philo->right]);
	philo_print(each_philo, PHILO_FORK);
	philo_print(each_philo, PHILO_EAT);
	ft_usleep(each_philo->time_to_eat);
	pthread_mutex_unlock(&ph->forks[each_philo->left]);
	pthread_mutex_unlock(&ph->forks[each_philo->right]);
}

void	philo_sleep(t_each_philo *each_philo)
{
	philo_print(each_philo, PHILO_SLEEP);
	ft_usleep(each_philo->time_to_sleep);
}

void	philo_think(t_each_philo *each_philo)
{
	philo_print(each_philo, PHILO_THINK);
}

void	*philo(void *each_philo_void)
{
	t_each_philo	*each_philo;
	t_philo_struct	*ph;

	each_philo = (t_each_philo *)each_philo_void;
	ph = each_philo->philo;
	pthread_mutex_init(&each_philo->eat_lock, NULL);
	while (each_philo->num_of_eat != 0)
	{
		if (each_philo->philo_id % 2 == 0)
			usleep(2500);
		philo_eat(each_philo, ph);
		if (each_philo->num_of_eat != -1)
		{
			pthread_mutex_lock(&each_philo->eat_lock);
			each_philo->num_of_eat--;
			pthread_mutex_unlock(&each_philo->eat_lock);
			if (each_philo->num_of_eat == 0)
				return (NULL);
		}
		philo_sleep(each_philo);
		philo_think(each_philo);
	}
	return (NULL);
}
