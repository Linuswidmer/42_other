/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:35:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/16 13:08:01 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* INCLUDES */

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define ALIVE 0
# define DEAD 1
# define INPUT_INSTRUCTION "INVALID INPUT: \nusage: \n \
	./philo num_philos time_to_die time_to_eat time_to_sleep (n_has_to_eat)\n"

/* STRUCTURES */
typedef struct s_data {
	int			num_philos;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	int			n_has_to_eat;
	long long	time_sim_start;
}	t_data;

typedef struct s_mutex {
	pthread_mutex_t	*arr_m_forks;
	pthread_mutex_t	*arr_m_philo_status;
	pthread_mutex_t	*arr_m_n_eaten;
	pthread_mutex_t	*arr_m_last_meal_ms;
	pthread_mutex_t	print;
}	t_mutex;

typedef struct s_philo {
	int				index;
	t_data			*data;
	t_mutex			*mutex;
	int				philo_status;
	int				n_eaten;
	long long		last_meal_ms;
}	t_philo;

typedef struct s_waiter {
	t_data			*data;
	t_mutex			*mutex;
	t_philo			*arr_philos;
}	t_waiter;

typedef enum e_exit_code {
	SUCCESS,
	MALLOC_FAIL,
	INPUT_FAIL,
	INIT_FAIL
}	t_exit_code;

typedef enum e_action{
	EAT,
	SLEEP,
	THINK,
	DIE,
	FORK
}	t_action;

/* FUNCTIONS */

/* libft_utils.c */
int			ft_atoi(const char *nptr);

/* philo_init.c */
t_exit_code	init(t_waiter **waiter, int argc, char **argv);

/*philo_print.c */
long long	current_timestamp_ms(void);
void		print_action(t_philo *philo, t_action action); 
void		philo_print_error_msg(t_exit_code exit_code);

/* philo_routine.c */
void		*philo_routine(void *p);
void		*philo_eat(t_philo *philo);

/* philo_utils.c */
void		philo_drop_forks(t_philo *philo);
void		*philo_pickup_forks(t_philo *philo);
int			get_n_eaten(t_philo *philo);
long long	get_last_meal_ms(t_philo *philo);
int			get_philo_status(t_philo *philo);

/* philo_monitor.c */
void		*monitor_threads(void *w);

/* philo_free.c */
void		free_all(t_waiter *waiter);

# endif
