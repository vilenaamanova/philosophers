/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:58 by ncathy            #+#    #+#             */
/*   Updated: 2022/05/26 11:54:42 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*malloc_struct(t_philo_struct *philo_struct, int philo_num)
{
	philo_struct->each_philo = (t_each_philo *)
		malloc(sizeof(t_each_philo) * philo_num);
	if (!philo_struct->each_philo)
		return (NULL);
	philo_struct->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * philo_num);
	if (!philo_struct->forks)
		return (NULL);
	philo_struct->philo = (pthread_t *)
		malloc(sizeof(pthread_t) * philo_num);
	if (!philo_struct->philo)
		return (NULL);
	return (0);
}

void	init_mutexes(t_philo_struct *philo_struct)
{
	pthread_mutex_init(&philo_struct->ate_last_time_lock, NULL);
	pthread_mutex_init(&philo_struct->is_dead_lock, NULL);
	pthread_mutex_init(&philo_struct->mes_lock, NULL);
	pthread_mutex_init(&philo_struct->eat_lock, NULL);
}

void	free_philo(t_philo_struct *philo_struct)
{
	if (philo_struct->philo)
		free(philo_struct->philo);
	if (philo_struct->forks)
		free(philo_struct->forks);
	if (philo_struct->each_philo)
		free(philo_struct->each_philo);
	free(philo_struct);
}

void	init(t_philo_struct *philo_struct)
{
	init_mutexes(philo_struct);
	init_forks(philo_struct);
	init_philo(philo_struct);
}

int	main(int argc, char **argv)
{
	t_philo_struct	*philo_struct;

	if (argc < 5 || argc > 6)
	{
		printf("Incorrect number of arguments!\n");
		return (-1);
	}
	else
	{
		philo_struct = (t_philo_struct *)malloc(sizeof(t_philo_struct));
		if (!philo_struct)
			return (-1);
		philo_struct = init_struct(philo_struct, argv);
		if (check_args(philo_struct, argc) == -1)
		{
			free(philo_struct);
			return (-1);
		}
		malloc_struct(philo_struct, philo_struct->philo_num);
		init(philo_struct);
		destroy_mutex(philo_struct);
		free_philo(philo_struct);
	}
	return (0);
}
