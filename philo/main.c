/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:58 by ncathy            #+#    #+#             */
/*   Updated: 2022/05/23 20:44:10 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
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
		malloc_struct(philo_struct, philo_struct->philo_num);
		init_forks(philo_struct);
		init_philo(philo_struct);
	}
	return (0);
}
