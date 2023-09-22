/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <lwidmer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:10:47 by lwidmer           #+#    #+#             */
/*   Updated: 2023/07/16 11:31:59 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_timestamp_ms(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

void	philo_print_error_msg(t_exit_code exit_code)
{
	if (exit_code == MALLOC_FAIL)
		printf("Dynamic memory allocation failed\n");
	else if (exit_code == INPUT_FAIL)
		printf(INPUT_INSTRUCTION);
	else if (exit_code == INIT_FAIL)
		printf("Fail in initialization\n");
}

void	print_action(t_philo *philo, t_action action)
{
	int			philo_index;
	long long	time;

	philo_index = philo->index + 1;
	if (get_philo_status(philo) == ALIVE)
	{
		pthread_mutex_lock(&philo->mutex->print);
		time = current_timestamp_ms() - philo->data->time_sim_start;
		if (action == EAT)
			printf("%lld %i is eating\n", time, philo_index);
		if (action == SLEEP)
			printf("%lld %i is sleeping\n", time, philo_index);
		if (action == THINK)
			printf("%lld %i is thinking\n", time, philo_index);
		if (action == FORK)
			printf("%lld %i has taken a fork\n", time, philo_index);
		pthread_mutex_unlock(&philo->mutex->print);
	}
}
