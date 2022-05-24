/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:22:29 by ncathy            #+#    #+#             */
/*   Updated: 2022/05/23 20:48:40 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_struct	*init_struct(t_philo_struct *philo_struct, char **argv)
{
	philo_struct->philo_num = ft_atoi(argv[1]);
	philo_struct->time_to_die = ft_atoi(argv[2]);
	philo_struct->time_to_eat = ft_atoi(argv[3]);
	philo_struct->time_to_sleep = ft_atoi(argv[4]);
	philo_struct->start_time = get_time();
	philo_struct->ate_last_time = philo_struct->start_time;
	philo_struct->num_of_eat = -1;
	if (argv[5])
		philo_struct->num_of_eat = ft_atoi(argv[5]);
	return (philo_struct);
}

void	init_forks(t_philo_struct *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->philo_num)
	{
		pthread_mutex_init(&philo_struct->forks[i], NULL);
		i++;
	}
}

void	init_philo(t_philo_struct *philo_struct)
{
	int	i;
	int	j;

	i = 0;
	while (i < philo_struct->philo_num)
	{
		philo_struct->each_philo[i].philo_num = philo_struct->philo_num;
		philo_struct->each_philo[i].time_to_die = philo_struct->time_to_die;
		philo_struct->each_philo[i].time_to_eat = philo_struct->time_to_eat;
		philo_struct->each_philo[i].time_to_sleep = philo_struct->time_to_sleep;
		philo_struct->each_philo[i].num_of_eat = philo_struct->num_of_eat;
		philo_struct->each_philo[i].philo_id = i + 1;
		philo_struct->each_philo[i].left = i;
		philo_struct->each_philo[i].right = (i + 1) % philo_struct->each_philo[i].philo_num;
		philo_struct->each_philo[i].start_time = philo_struct->start_time;
		philo_struct->each_philo[i].ate_last_time = philo_struct->ate_last_time;
		philo_struct->each_philo[i].philo = philo_struct;
		pthread_create(&philo_struct->philo[i], NULL, philo, &philo_struct->each_philo[i]);
		i++;
	}
	j = 0;
	while (j < philo_struct->philo_num)
	{
		pthread_join(philo_struct->philo[j], NULL);
		j++;
	}
}
