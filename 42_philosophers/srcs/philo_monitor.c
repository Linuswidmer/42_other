/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:20:47 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/16 13:14:06 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_simulation(t_waiter *waiter, int index)
{
	int			i;
	long long	time;

	i = 0;
	time = current_timestamp_ms();
	while (i < waiter->data->num_philos)
	{
		pthread_mutex_lock(&(waiter->mutex->arr_m_philo_status[i]));
		waiter->arr_philos[i].philo_status = 1;
		pthread_mutex_unlock(&(waiter->mutex->arr_m_philo_status[i]));
		i++;
	}
	if (index >= 0)
	{
		pthread_mutex_lock(&waiter->mutex->print);
		printf("%lld %i died\n", time - waiter->data->time_sim_start, index + 1);
		pthread_mutex_unlock(&waiter->mutex->print);
	}
}

int	monitor_check_philo_status(t_waiter *waiter)
{
	int			i;
	long long	time_now;
	long long	ms_since_last_meal;
	t_philo		*philo;

	i = 0;
	time_now = current_timestamp_ms();
	while (i < waiter->data->num_philos)
	{
		philo = &waiter->arr_philos[i];
		ms_since_last_meal = time_now - get_last_meal_ms(philo);
		if (ms_since_last_meal > (waiter->data->time_to_die / 1000))
			return (philo->index);
		i++;
	}
	return (-1);
}

int	monitor_check_n_eaten(t_waiter *waiter)
{
	int	i;
	int	n_eaten;

	i = 0;
	while (i < waiter->data->num_philos)
	{
		n_eaten = get_n_eaten(&waiter->arr_philos[i]);
		if (n_eaten >= waiter->data->n_has_to_eat)
			i++;
		else
			break ;
	}
	if (i == waiter->data->num_philos)
		return (1);
	else
		return (0);
}

void	*monitor_threads(void *w)
{
	int			index;
	t_waiter	*waiter;

	waiter = (t_waiter *)w;
	while (1)
	{
		index = monitor_check_philo_status(waiter);
		if (index >= 0)
		{
			end_simulation(waiter, index);
			break ;
		}
		if (monitor_check_n_eaten(waiter) == 1
			&& waiter->data->n_has_to_eat >= 0)
		{
			end_simulation(waiter, -1);
			break ;
		}
		usleep (5000);
	}
	return (NULL);
}
