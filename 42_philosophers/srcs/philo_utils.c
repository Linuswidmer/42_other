/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:17:13 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/16 12:49:49 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_philo_status(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->arr_m_philo_status[philo->index]));
	if (philo->philo_status == 1)
	{
		pthread_mutex_unlock(&(philo->mutex->arr_m_philo_status[philo->index]));
		return (DEAD);
	}
	else
	{
		pthread_mutex_unlock(&(philo->mutex->arr_m_philo_status[philo->index]));
		return (ALIVE);
	}
}

long long	get_last_meal_ms(t_philo *philo)
{
	long long	last_meal_ms;

	pthread_mutex_lock(&(philo->mutex->arr_m_last_meal_ms[philo->index]));
	last_meal_ms = philo->last_meal_ms;
	pthread_mutex_unlock(&(philo->mutex->arr_m_last_meal_ms[philo->index]));
	return (last_meal_ms);
}

int	get_n_eaten(t_philo *philo)
{
	int	n_eaten;

	pthread_mutex_lock(&(philo->mutex->arr_m_n_eaten[philo->index]));
	n_eaten = philo->n_eaten;
	pthread_mutex_unlock(&(philo->mutex->arr_m_n_eaten[philo->index]));
	return (n_eaten);
}

void	*philo_pickup_forks(t_philo *philo)
{
	int	philo_index;
	int	last_philo;

	if (get_philo_status(philo) == DEAD)
		return (NULL);
	philo_index = philo->index;
	last_philo = philo->data->num_philos - 1;
	if (philo_index % 2 == 0 || (philo->data->num_philos % 2
			&& philo_index == last_philo))
	{
		pthread_mutex_lock(&(philo->mutex->arr_m_forks[(philo_index + 1)
				% philo->data->num_philos]));
		print_action(philo, FORK);
		pthread_mutex_lock(&(philo->mutex->arr_m_forks[philo_index]));
		print_action(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&(philo->mutex->arr_m_forks[philo_index]));
		print_action(philo, FORK);
		pthread_mutex_lock(&(philo->mutex->arr_m_forks[(philo_index + 1)
				% philo->data->num_philos]));
		print_action(philo, FORK);
	}
	return (NULL);
}

void	philo_drop_forks(t_philo *philo)
{
	int	philo_index;
	int	last_philo;

	philo_index = philo->index;
	last_philo = philo->data->num_philos - 1;
	if (philo_index % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->mutex->arr_m_forks[(philo_index + 1)
				% philo->data->num_philos]));
		pthread_mutex_unlock(&(philo->mutex->arr_m_forks[philo_index]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->mutex->arr_m_forks[philo_index]));
		pthread_mutex_unlock(&(philo->mutex->arr_m_forks[(philo_index + 1)
				% philo->data->num_philos]));
	}
}
