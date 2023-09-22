/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:06:03 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:42:32 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack *stack)
{
	int		i;
	t_elem	*first;
	t_elem	*tmp;

	i = 0;
	first = stack->first;
	while (i < stack->size)
	{
		tmp = first->next;
		free(first);
		first = tmp;
		i++;
	}
	free(stack);
}

void	free_split_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

void	terminate_on_success(t_data *data)
{
	free_split_arr(data->split_arr);
	free_stack(data->stack_a);
	free_stack(data->stack_b);
	free (data);
}

void	terminate_on_error(t_data *data)
{
	if (data->split_arr)
		free_split_arr(data->split_arr);
	if (data->stack_a)
		free_stack(data->stack_a);
	if (data->stack_b)
		free_stack(data->stack_b);
	if (data)
		free (data);
	write (2, "Error\n", 6);
	exit (1);
}
