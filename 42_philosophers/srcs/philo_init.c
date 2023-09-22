/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:22:53 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/16 13:16:37 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_exit_code	init_data(t_data **p_data, int argc, char **argv)
{
	static t_exit_code	exit_code;
	t_data				*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_code = MALLOC_FAIL;
	if (exit_code == SUCCESS)
	{
		data->num_philos = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]) * 1000; 
		data->time_to_eat = ft_atoi(argv[3]) * 1000;
		data->time_to_sleep = ft_atoi(argv[4]) * 1000;
		data->time_sim_start = current_timestamp_ms();
		if (argc == 6)
			data->n_has_to_eat = ft_atoi(argv[5]);
		else
			data->n_has_to_eat = -1;
	}
	*p_data = data;
	return (exit_code);
}

t_exit_code	init_philos(t_philo **p_arr_philos, t_data *data, t_mutex *mutex)
{
	t_exit_code	exit_code;
	t_philo		*arr_philos;
	int			i;

	i = 0;
	exit_code = SUCCESS;
	arr_philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!arr_philos)
		exit_code = MALLOC_FAIL;
	if (exit_code == SUCCESS)
	{
		while (i < data->num_philos)
		{
			(arr_philos[i]).index = i;
			(arr_philos[i]).data = data;
			(arr_philos[i]).mutex = mutex;
			(arr_philos[i]).n_eaten = 0;
			(arr_philos[i]).philo_status = ALIVE;
			(arr_philos[i]).last_meal_ms = current_timestamp_ms();
			i++;
		}
	}
	*p_arr_philos = arr_philos;
	return (exit_code);
}

t_exit_code	init_mutex(t_mutex *mutex, int n_philos)
{
	static int				i;
	static t_exit_code		exit;

	mutex->arr_m_forks = malloc(sizeof(pthread_mutex_t) * n_philos);
	mutex->arr_m_philo_status = malloc(sizeof(pthread_mutex_t) * n_philos);
	mutex->arr_m_n_eaten = malloc(sizeof(pthread_mutex_t) * n_philos);
	mutex->arr_m_last_meal_ms = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (mutex->arr_m_forks && mutex->arr_m_philo_status && mutex->arr_m_n_eaten
		&& mutex->arr_m_last_meal_ms)
	{
		pthread_mutex_init(&mutex->print, NULL);
		while (i < n_philos)
		{
			pthread_mutex_init(&(mutex->arr_m_philo_status[i]), NULL);
			pthread_mutex_init(&(mutex->arr_m_last_meal_ms[i]), NULL);
			pthread_mutex_init(&(mutex->arr_m_n_eaten[i]), NULL);
			pthread_mutex_init(&(mutex->arr_m_forks[i]), NULL);
			i++;
		}
	}
	else
		exit = MALLOC_FAIL;
	return (exit);
}

t_exit_code	init_waiter(t_waiter **p_waiter, t_data *data, t_mutex *mutex,
								t_philo *arr_philos)
{
	t_exit_code	exit_code;
	t_waiter	*waiter;
	int			i;

	i = 0;
	exit_code = SUCCESS;
	waiter = malloc(sizeof(t_waiter));
	if (!waiter)
		return (MALLOC_FAIL);
	waiter->data = data;
	waiter->mutex = mutex;
	waiter->arr_philos = arr_philos;
	*p_waiter = waiter;
	return (exit_code);
}

t_exit_code	init(t_waiter **waiter, int argc, char **argv)
{
	t_exit_code	exit;
	t_data		*data;
	t_mutex		*mutex;
	t_philo		*philos;

	exit = init_data(&data, argc, argv);
	mutex = malloc(sizeof(t_mutex));
	if (!mutex)
		exit = MALLOC_FAIL;
	if (exit == SUCCESS)
		exit = init_mutex(mutex, data->num_philos);
	if (exit == SUCCESS)
		exit = init_philos(&philos, data, mutex);
	if (exit == SUCCESS)
		exit = init_waiter(waiter, data, mutex, philos);
	return (exit);
}
