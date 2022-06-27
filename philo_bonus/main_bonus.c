/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:34:45 by ncathy            #+#    #+#             */
/*   Updated: 2022/06/27 13:27:37 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_philos(t_philo_struct *philo_struct)
{
	int	i;
	int	status;

	i = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
			while (i < philo_struct->philo_num)
			{
				kill(philo_struct->each_philo[i].pid, SIGKILL);
				i++;
			}
		}
	}
}

static void	remove_sems(t_philo_struct *philo_struct)
{
	sem_close(philo_struct->fork);
	sem_close(philo_struct->mes);
	sem_unlink("forks");
	sem_unlink("mes");
}

void	get_each_pid(t_philo_struct *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->philo_num)
	{
		philo_struct->each_philo[i].pid = fork();
		if (philo_struct->each_philo[i].pid == 0)
			philo(philo_struct, i);
		i++;
	}
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
			exit(1);
		}
		init_sem(philo_struct);
		get_each_pid(philo_struct);
		kill_philos(philo_struct);
		remove_sems(philo_struct);
	}
	return (0);
}
