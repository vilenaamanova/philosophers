/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:40:30 by ncathy            #+#    #+#             */
/*   Updated: 2022/06/26 11:03:25 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print(t_philo_struct *ph, t_each_philo *each_philo, int philo_code)
{
	long	current_time;

	current_time = get_time() - each_philo->start_time;
	pthread_mutex_lock(&ph->mes_lock);
	if (philo_code == PHILO_EAT)
		printf("[%ld] %d is eating\n", current_time, each_philo->philo_id);
	else if (philo_code == PHILO_FORK)
		printf("[%ld] %d has taken a fork\n",
			current_time, each_philo->philo_id);
	else if (philo_code == PHILO_SLEEP)
		printf("[%ld] %d is sleeping\n", current_time, each_philo->philo_id);
	else if (philo_code == PHILO_THINK)
		printf("[%ld] %d is thinking\n", current_time, each_philo->philo_id);
	else if (philo_code == PHILO_DIED)
	{
		printf("[%ld] %d died\n", current_time, each_philo->philo_id);
		return (0);
	}
	pthread_mutex_unlock(&ph->mes_lock);
	return (0);
}

int	check_args(t_philo_struct *philo_struct, int argc)
{
	if (philo_struct->philo_num <= 0 || philo_struct->philo_num >= 200)
	{
		error_mes(NUM_ERROR);
		return (-1);
	}
	else if (philo_struct->time_to_die <= 0)
	{
		error_mes(TTD_ERROR);
		return (-1);
	}
	else if (check_args_pt2(philo_struct) == -1)
		return (-1);
	if (argc == 6)
	{
		if (philo_struct->num_of_eat <= 0)
		{
			error_mes(EATNUM_ERROR);
			return (-1);
		}	
	}
	return (0);
}

int	check_args_pt2(t_philo_struct *philo_struct)
{
	if (philo_struct->time_to_eat <= 0)
	{
		error_mes(TTE_ERROR);
		return (-1);
	}
	else if (philo_struct->time_to_sleep <= 0)
	{
		error_mes(TTS_ERROR);
		return (-1);
	}
	return (0);
}

void	error_mes(int error_code)
{
	if (error_code == NUM_ERROR)
		write(2, "Wrong [number_of_philosophers] arguments!\n", 42);
	else if (error_code == TTD_ERROR)
		write(2, "Wrong [time_to_die] argument!\n", 30);
	else if (error_code == TTE_ERROR)
		write(2, "Wrong [time_to_eat] argument!\n", 30);
	else if (error_code == TTS_ERROR)
		write(2, "Wrong [time_to_sleep] argument!\n", 32);
	else if (error_code == EATNUM_ERROR)
		write(2, "Wrong [num_of_eat] argument!\n", 29);
}

void	destroy_mutex(t_philo_struct *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->philo_num)
	{
		pthread_mutex_destroy(&philo_struct->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo_struct->ate_last_time_lock);
	pthread_mutex_destroy(&philo_struct->is_dead_lock);
	pthread_mutex_destroy(&philo_struct->mes_lock);
	pthread_mutex_destroy(&philo_struct->eat_lock);
}
