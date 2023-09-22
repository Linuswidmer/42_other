/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:32:39 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/16 13:07:24 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_exit_code	run_simulation(t_waiter *waiter)
{
	int			i;
	pthread_t	*arr_threads_philo;
	pthread_t	thread_waiter;

	i = 0;
	arr_threads_philo = malloc(sizeof(pthread_t) * waiter->data->num_philos);
	if (!arr_threads_philo)
		return (MALLOC_FAIL);
	pthread_create(&(thread_waiter), NULL, monitor_threads, waiter);
	while (i < waiter->data->num_philos)
	{
		pthread_create(&(arr_threads_philo[i]), NULL, philo_routine,
			&(waiter->arr_philos)[i]);
		i++;
	}
	i = 0;
	while (i < waiter->data->num_philos)
	{
		pthread_join(arr_threads_philo[i], NULL);
		i++;
	}
	pthread_join(thread_waiter, NULL);
	free(arr_threads_philo);
	return (SUCCESS);
}

t_exit_code	philo_check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			if (ft_atoi(argv[i]) <= 0)
				return (INPUT_FAIL);
			i++;
		}
		return (SUCCESS);
	}
	return (INPUT_FAIL);
}

int	main(int argc, char **argv)
{
	t_waiter	*waiter;
	t_exit_code	exit;

	exit = philo_check_input(argc, argv);
	if (exit == SUCCESS)
		exit = init(&waiter, argc, argv);
	if (exit == SUCCESS)
		exit = run_simulation(waiter);
	if (exit != INPUT_FAIL)
		free_all(waiter);
	if (exit != SUCCESS)
		philo_print_error_msg(exit);
	return (exit);
}
