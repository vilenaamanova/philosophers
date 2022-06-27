/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:41:48 by ncathy            #+#    #+#             */
/*   Updated: 2022/06/27 13:27:30 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo_struct	*init_struct(t_philo_struct *philo_struct, char **argv)
{
	philo_struct->philo_num = ft_atoi(argv[1]);
	philo_struct->time_to_die = ft_atoi(argv[2]);
	philo_struct->time_to_eat = ft_atoi(argv[3]);
	philo_struct->time_to_sleep = ft_atoi(argv[4]);
	philo_struct->num_of_eat = -1;
	philo_struct->philo_id = -1;
	philo_struct->start_time = get_time();
	philo_struct->each_philo = (t_each_philo *)malloc(sizeof(t_each_philo)
			* philo_struct->philo_num);
	if (!philo_struct->each_philo)
		return (NULL);
	if (argv[5])
		philo_struct->num_of_eat = ft_atoi(argv[5]);
	return (philo_struct);
}

int	init_sem(t_philo_struct *philo_struct)
{
	philo_struct->mes = sem_open("mes", O_CREAT, 0777, 1);
	if (philo_struct->mes == SEM_FAILED)
		return (-1);
	philo_struct->fork = sem_open("forks", O_CREAT,
			0777, philo_struct->philo_num);
	if (philo_struct->fork == SEM_FAILED)
		return (-1);
	return (0);
}
