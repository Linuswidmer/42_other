/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:59:51 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:31:47 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Returns an empirically good chunk size depending on the number of elements
that will have to be sorted.
*/
int	calc_chunk_size(int size)
{
	if (size <= 10)
		return (2);
	else if (size <= 20)
		return (3);
	else if (size < 50)
		return (4);
	else if (size < 500)
		return (5);
	else
		return (13);
}

/*
Compares whether an element can be brought to the top of a stack with less
operations when using rotations or reverse rotations.
E.g. Rotating a stack of size 5 four times is the same as reverse rotating it 
once, saving 3 operations.
*/
t_data	*rotate_optimization(t_data *data, int rotations, char which)
{
	if (rotations > (data->stack_a->size / 2))
	{
		rotations = data->stack_a->size - rotations;
		data = apply_rev_rotations(data, rotations, which);
	}
	else
		data = apply_rotations(data, rotations, which);
	return (data);
}

/*
checks whether a stack is already sorted
*/
int	is_sorted(t_stack *stack)
{
	int		i;
	t_elem	*tmp;

	i = 0;
	tmp = stack->first;
	while (i < stack->size)
	{
		if (i != tmp->num)
			break ;
		i++;
		tmp = tmp->next;
	}
	if (i == stack->size)
		return (1);
	else
		return (0);
}

/*
depending on the number of elements to sort, elicits the different sorting
mechanisms
*/
t_data	*sorting_decision(t_data *data, int size)
{
	if (is_sorted(data->stack_a) == 1)
		return (data);
	if (size == 2)
		data = sort_two(data);
	else if (size == 3)
		data = sort_three(data);
	else if (size <= 5)
		data = sort_four_five(data);
	else
		data = chunk_sort(data);
	return (data);
}
