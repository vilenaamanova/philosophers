/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:21:58 by ncathy            #+#    #+#             */
/*   Updated: 2022/06/21 23:09:24 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo(t_philo_struct *philo_struct, int i)
{
	philo_struct->philo_id = i + 1;
	philo_struct->each_philo[i].ate_last_time = philo_struct->start_time;
	pthread_create(&philo_struct->philo_is_dead,
		NULL, &philo_is_dead, philo_struct);
	while (philo_struct->num_of_eat != 0)
	{
		philo_eat(philo_struct, i);
		if (philo_struct->num_of_eat != -1)
		{
			philo_struct->num_of_eat--;
			if (philo_struct->num_of_eat == 0)
				exit (0);
		}
		philo_sleep(philo_struct);
		philo_think(philo_struct);
	}
	pthread_join(philo_struct->philo_is_dead, NULL);
	return (NULL);
}

void	philo_eat(t_philo_struct *philo_struct, int i)
{
	sem_wait(philo_struct->fork);
	philo_print(philo_struct, PHILO_FORK);
	sem_wait(philo_struct->fork);
	philo_print(philo_struct, PHILO_FORK);
	philo_print(philo_struct, PHILO_EAT);
	ft_usleep(philo_struct->time_to_eat);
	philo_struct->each_philo[i].ate_last_time = get_time();
	sem_post(philo_struct->fork);
	sem_post(philo_struct->fork);
}

void	philo_sleep(t_philo_struct *philo_struct)
{
	philo_print(philo_struct, PHILO_SLEEP);
	ft_usleep(philo_struct->time_to_sleep);
}

void	philo_think(t_philo_struct *philo_struct)
{
	philo_print(philo_struct, PHILO_THINK);
}

void	*philo_is_dead(void *philo_struct_void)
{
	int				i;
	t_philo_struct	*philo_struct;

	philo_struct = (t_philo_struct *)philo_struct_void;
	i = philo_struct->philo_id - 1;
	while (1)
	{
		if (get_time() - philo_struct->each_philo[i].ate_last_time
			>= philo_struct->time_to_die)
		{
			philo_print(philo_struct, PHILO_DIED);
			exit (1);
		}
		usleep(500);
	}
	return (NULL);
}
