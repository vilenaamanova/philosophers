/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:57:08 by ncathy            #+#    #+#             */
/*   Updated: 2022/06/21 23:17:08 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

# define PHILO_EAT 2
# define PHILO_SLEEP 3
# define PHILO_THINK 4
# define PHILO_FORK 5
# define PHILO_DIED 6
# define NUM_ERROR 7
# define TTD_ERROR 8
# define TTE_ERROR 9
# define TTS_ERROR 10
# define EATNUM_ERROR 11

typedef struct s_each_philo {
	long				ate_last_time;
	pid_t				pid;
}	t_each_philo;

typedef struct s_philo_struct {
	int					philo_num;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					num_of_eat;
	int					philo_id;
	long				start_time;
	sem_t				*fork;
	sem_t				*mes;
	pthread_t			philo_is_dead;
	struct s_each_philo	*each_philo;
}	t_philo_struct;

/* libft */
int						ft_atoi(const char *str);

/* init */
t_philo_struct			*init_struct(t_philo_struct *philo_struct, char **argv);
int						init_sem(t_philo_struct *philo_struct);
void					get_each_pid(t_philo_struct *philo_struct);

/* simulate */
void					*philo(t_philo_struct *philo_struct, int i);
void					philo_eat(t_philo_struct *philo_struct, int i);
void					philo_sleep(t_philo_struct *philo_struct);
void					philo_think(t_philo_struct *philo_struct);
void					*philo_is_dead(void *philo_struct_void);

/* time */
long					get_time(void);
int						ft_usleep(long mseconds);

/* utils */
int						philo_print(t_philo_struct *ph, int philo_code);
void					error_mes(int error_code);
int						check_args(t_philo_struct *philo_struct, int argc);
void					free_struct(t_philo_struct *philo_struct);

int						main(int argc, char **argv);

#endif
