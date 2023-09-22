/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:33:49 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/16 10:49:37 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_data(t_data *data)
{
	free(data);
}

static void	free_philo(t_philo *philo)
{
	free(philo);
}

static void	free_mutex(t_mutex *mutex, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_destroy(&(mutex->arr_m_philo_status[i]));
		pthread_mutex_destroy(&(mutex->arr_m_last_meal_ms[i]));
		pthread_mutex_destroy(&(mutex->arr_m_n_eaten[i]));
		pthread_mutex_destroy(&(mutex->arr_m_forks[i]));
		i++;
	}
	free(mutex->arr_m_forks);
	free(mutex->arr_m_n_eaten);
	free(mutex->arr_m_last_meal_ms);
	free(mutex->arr_m_philo_status);
	free(mutex);
}

static void	free_waiter(t_waiter *waiter)
{
	free(waiter);
}

void	free_all(t_waiter *waiter)
{
	int	n_philos;
	int	i;

	i = 0;
	n_philos = waiter->data->num_philos;
	free_data(waiter->data);
	free_philo(waiter->arr_philos);
	free_mutex(waiter->mutex, n_philos);
	free_waiter(waiter);
}
