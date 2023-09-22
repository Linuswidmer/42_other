/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:04:55 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/16 12:38:22 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (get_philo_status(philo) == ALIVE)
	{
		print_action(philo, THINK);
		usleep(((data->time_to_die - (data->time_to_eat
						+ data->time_to_sleep)) / 2));
		philo_eat(philo);
	}
	return (NULL);
}

void	*philo_sleep(t_philo *philo)
{
	if (get_philo_status(philo) == ALIVE)
	{
		print_action(philo, SLEEP);
		usleep(philo->data->time_to_sleep);
		philo_think(philo);
	}
	return (NULL);
}

void	*philo_eat(t_philo *philo)
{
	if (get_philo_status(philo) == DEAD)
		return (NULL);
	philo_pickup_forks(philo);
	if (get_philo_status(philo) == DEAD)
	{
		philo_drop_forks(philo);
		return (NULL);
	}
	print_action(philo, EAT);
	pthread_mutex_lock(&(philo->mutex->arr_m_last_meal_ms[philo->index]));
	philo->last_meal_ms = current_timestamp_ms();
	pthread_mutex_unlock(&(philo->mutex->arr_m_last_meal_ms[philo->index]));
	usleep(philo->data->time_to_eat);
	if (get_philo_status(philo) == DEAD)
	{
		philo_drop_forks(philo);
		return (NULL);
	}
	pthread_mutex_lock(&(philo->mutex->arr_m_n_eaten[philo->index]));
	philo->n_eaten = philo->n_eaten + 1;
	pthread_mutex_unlock(&(philo->mutex->arr_m_n_eaten[philo->index]));
	philo_drop_forks(philo);
	philo_sleep(philo);
	return (NULL);
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->data->num_philos == 1)
		return (NULL);
	if (philo->index % 2 != 0)
		usleep(philo->data->time_to_eat / 4);
	philo_eat(philo);
	return (NULL);
}
