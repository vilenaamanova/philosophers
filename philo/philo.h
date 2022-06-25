/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:32:28 by ncathy            #+#    #+#             */
/*   Updated: 2022/05/26 12:02:51 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

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

typedef struct s_philo_struct {
	int						philo_num;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	int						num_of_eat;
	long					start_time;
	long					ate_last_time;
	int						philo_died;
	pthread_t				*philo;
	pthread_t				monitor;
	pthread_mutex_t			*forks;
	pthread_mutex_t			ate_last_time_lock;
	pthread_mutex_t			is_dead_lock;
	pthread_mutex_t			mes_lock;
	pthread_mutex_t			eat_lock;
	struct s_each_philo		*each_philo;
}	t_philo_struct;

typedef struct s_each_philo {
	int						num_of_eat;
	int						philo_id;
	int						left;
	int						right;
	long					start_time;
	long					ate_last_time;
	struct s_philo_struct	*philo;
}	t_each_philo;

/* libft */
int				ft_atoi(const char *str);

/* init */
t_philo_struct	*init_struct(t_philo_struct *philo_struct, char **argv);
void			init_forks(t_philo_struct *philo_struct);
void			*init_philo(t_philo_struct *philo_struct);
void			init_philo_values(t_philo_struct *philo_struct);
void			init_mutexes(t_philo_struct *philo_struct);
void			init(t_philo_struct *philo_struct);

/* simulate */
void			*philo(void *each_philo_void);
void			philo_eat(t_each_philo *each_philo, t_philo_struct *ph);
void			philo_sleep(t_each_philo *each_philo, t_philo_struct *ph);
void			philo_think(t_each_philo *each_philo, t_philo_struct *ph);
int				philo_is_dead(t_philo_struct *philo_struct);

/* time */
long			get_time(void);
int				ft_usleep(long mseconds);

/* utils */
int				philo_print(t_philo_struct *ph,
					t_each_philo *each_philo, int philo_code);
void			*malloc_struct(t_philo_struct *philo_struct, int philo_num);
int				check_args(t_philo_struct *philo_struct, int argc);
int				check_args_pt2(t_philo_struct *philo_struct);
void			error_mes(int error_code);
void			destroy_mutex(t_philo_struct *philo_struct);

int				main(int argc, char **argv);

#endif
