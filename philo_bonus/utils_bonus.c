/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:38:47 by ncathy            #+#    #+#             */
/*   Updated: 2022/06/21 23:14:37 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_print(t_philo_struct *ph, int philo_code)
{
	long	current_time;

	current_time = get_time() - ph->start_time;
	sem_wait(ph->mes);
	if (philo_code == PHILO_EAT)
		printf("[%ld] %d is eating\n", current_time, ph->philo_id);
	else if (philo_code == PHILO_FORK)
		printf("[%ld] %d has taken a fork\n", current_time, ph->philo_id);
	else if (philo_code == PHILO_SLEEP)
		printf("[%ld] %d is sleeping\n", current_time, ph->philo_id);
	else if (philo_code == PHILO_THINK)
		printf("[%ld] %d is thinking\n", current_time, ph->philo_id);
	else if (philo_code == PHILO_DIED)
	{
		printf("[%ld] %d died\n", current_time, ph->philo_id);
		return (0);
	}
	sem_post(ph->mes);
	return (0);
}

int	check_args(t_philo_struct *philo_struct, int argc)
{
	if (philo_struct->philo_num <= 0 || philo_struct->philo_num >= 200)
		error_mes(NUM_ERROR);
	else if (philo_struct->time_to_die <= 0)
		error_mes(TTD_ERROR);
	else if (philo_struct->time_to_eat <= 0)
		error_mes(TTE_ERROR);
	else if (philo_struct->time_to_sleep <= 0)
		error_mes(TTS_ERROR);
	if (argc == 6)
	{
		if (philo_struct->num_of_eat <= 0)
			error_mes(EATNUM_ERROR);
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
		write(2, "Wrong [number_of_eat] argument!\n", 32);
	exit (1);
}

void	free_struct(t_philo_struct *philo_struct)
{
	if (philo_struct)
		free(philo_struct);
}
