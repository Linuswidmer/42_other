/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:36:18 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:36:59 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
If stack is not already sorted, only needs one swap
*/
t_data	*sort_two(t_data *data)
{
	int	first;
	int	second;

	first = data->stack_a->first->num;
	second = data->stack_a->first->next->num;
	if (first < second)
		return (data);
	else
		return (swap(data, 'a'));
}

/*
Depending on the order of the three elements uses a hard coded sequence
of instructions to optimize the number of operations.
*/
t_data	*sort_three(t_data *data)
{
	int	first;
	int	second;
	int	third;

	first = data->stack_a->first->num;
	second = data->stack_a->first->next->num;
	third = data->stack_a->first->prev->num;
	if (first > second && second < third && third > first)
		data = swap(data, 'a');
	else if (first > second && second < third && third < first)
		data = rotate(data, 'a');
	else if (first > second && second > third)
	{
		data = swap(data, 'a');
		data = rev_rotate(data, 'a');
	}
	else if (first < second && second > third && third > first)
	{
		data = swap(data, 'a');
		data = rotate(data, 'a');
	}
	else if (first < second && second > third && third < first)
		data = rev_rotate(data, 'a');
	return (data);
}
