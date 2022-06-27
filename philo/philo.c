/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:41:42 by ncathy            #+#    #+#             */
/*   Updated: 2022/06/27 11:15:37 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_each_philo *each_philo, t_philo_struct *ph)
{
	pthread_mutex_lock(&ph->forks[each_philo->left]);
	philo_print(ph, each_philo, PHILO_FORK);
	pthread_mutex_lock(&ph->forks[each_philo->right]);
	philo_print(ph, each_philo, PHILO_FORK);
	philo_print(ph, each_philo, PHILO_EAT);
	pthread_mutex_lock(&ph->ate_last_time_lock);
	each_philo->ate_last_time = get_time();
	pthread_mutex_unlock(&ph->ate_last_time_lock);
	ft_usleep(ph->time_to_eat);
	pthread_mutex_unlock(&ph->forks[each_philo->left]);
	pthread_mutex_unlock(&ph->forks[each_philo->right]);
}

void	philo_sleep(t_each_philo *each_philo, t_philo_struct *ph)
{
	philo_print(ph, each_philo, PHILO_SLEEP);
	ft_usleep(ph->time_to_sleep);
}

void	philo_think(t_each_philo *each_philo, t_philo_struct *ph)
{
	philo_print(ph, each_philo, PHILO_THINK);
}

void	*philo(void *each_philo_void)
{
	t_each_philo	*each_philo;
	t_philo_struct	*ph;

	each_philo = (t_each_philo *)each_philo_void;
	ph = each_philo->philo;
	while (each_philo->num_of_eat != 0)
	{
		if (each_philo->philo_id % 2 == 0)
			usleep(2500);
		philo_eat(each_philo, ph);
		if (each_philo->num_of_eat != -1)
		{
			pthread_mutex_lock(&ph->eat_lock);
			each_philo->num_of_eat--;
			pthread_mutex_unlock(&ph->eat_lock);
			if (each_philo->num_of_eat == 0)
				return (NULL);
		}
		philo_sleep(each_philo, ph);
		philo_think(each_philo, ph);
	}
	return (NULL);
}

int	philo_is_dead(t_philo_struct *ph)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < ph->philo_num)
		{
			pthread_mutex_lock(&ph->eat_lock);
			if (ph->each_philo[i].num_of_eat == 0)
			{
				pthread_mutex_unlock(&ph->eat_lock);
				return (0);
			}
			pthread_mutex_unlock(&ph->eat_lock);
			if (is_philo_going_to_die(ph, i) == 1)
			{
				philo_print(ph, &ph->each_philo[i], PHILO_DIED);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
