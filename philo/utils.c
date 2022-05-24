/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:40:30 by ncathy            #+#    #+#             */
/*   Updated: 2022/05/23 20:31:52 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print(t_each_philo *each_philo, int philo_code)
{
	long	current_time;

	current_time = get_time() - each_philo->start_time;
	pthread_mutex_lock(&each_philo->mes_lock);
	if (philo_code == PHILO_EAT)
		printf("[%ld] %d is eating\n", current_time, each_philo->philo_id);
	else if (philo_code == PHILO_FORK)
		printf("[%ld] %d has taken a fork\n", current_time, each_philo->philo_id);
	else if (philo_code == PHILO_SLEEP)
		printf("[%ld] %d is sleeping\n", current_time, each_philo->philo_id);
	else if (philo_code == PHILO_THINK)
		printf("[%ld] %d is thinking\n", current_time, each_philo->philo_id);
	else if (philo_code == PHILO_DIED)
	{
		printf("[%ld] %d died\n", current_time, each_philo->philo_id);
		return (0);
	}
	pthread_mutex_unlock(&each_philo->mes_lock);
	return (0);
}

void	*malloc_struct(t_philo_struct *philo_struct, int philo_num)
{
	philo_struct->each_philo = (t_each_philo *)malloc(sizeof(t_each_philo) * philo_num);
	if (!philo_struct->each_philo)
		return (NULL);
	philo_struct->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_num);
	if (!philo_struct->forks)
		return (NULL);
	philo_struct->philo = (pthread_t *)malloc(sizeof(pthread_t) * philo_num);
	if (!philo_struct->philo)
		return (NULL);
	return (0);
}
