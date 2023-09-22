/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_four_five.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:12:41 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 17:08:42 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
rotates a sorted list, so that the smallest element is on top
*/
t_data	*rotate_sorted_list(t_data *data, char which)
{
	int		rotations;
	t_elem	*tmp;

	rotations = 0;
	tmp = data->stack_a->first;
	while (tmp->num != 0)
	{
		tmp = tmp->next;
		rotations++;
	}
	data = rotate_optimization(data, rotations, which);
	return (data);
}

/*
if the two neighbouring numbers in a stack can be found, rotates this stack
so that the number can be 'inserted' by pushing it on top of the stack
*/
t_data	*insert_adjacent_found(t_data *data)
{
	int		rotations;
	t_elem	*tmp;

	rotations = 0;
	tmp = data->stack_a->first;
	while (rotations < data->stack_a->size)
	{
		if (tmp->prev->num < data->stack_b->first->num && tmp->num
			> data->stack_b->first->num)
		{
			break ;
		}
		tmp = tmp->next;
		rotations++;
	}
	data = rotate_optimization(data, rotations, 'a');
	data = push(data, 'a');
	return (data);
}

/*
if the two neighbouring numbers in a stack cannot be found, searches for
its nearest neighbours and rotates this stack so that the number can be 
'inserted' by pushing it on top of the stack
*/
t_data	*insert_adjacent_not_found(t_data *data, t_elem *tmp, int sign)
{
	int		rotations;
	int		dif;

	dif = 0;
	while (dif++ < 3)
	{
		rotations = 0;
		while (rotations < data->stack_a->size)
		{
			if (data->stack_b->first->num + (dif * sign) == tmp->num)
				break ;
			tmp = tmp->next;
			rotations++;
		}
		if (rotations < data->stack_a->size)
			break ;
	}
	data = rotate_optimization(data, rotations, 'a');
	data = push(data, 'a');
	return (data);
}

/*
adjacent numbers cannot be found in the case of five elements, if the first
element that is to be sorted is the smalles (0) or the biggest (4) element.
*/
t_data	*insertion_sort(t_data *data)
{
	if (data->stack_b->first->num == 0 || data->stack_b->first->num == 4)
	{
		if (data->stack_b->first->num == 0)
			data = insert_adjacent_not_found(data, data->stack_a->first, 1);
		else if (data->stack_b->first->num == 4)
			data = insert_adjacent_not_found(data,
					data->stack_a->first->prev, -1);
	}
	else
		data = insert_adjacent_found(data);
	return (data);
}

/*
Calls the functions from above, pushing first two (or in the case of stack size
four 1) elements to stack b, sorts stack a and inserts two (or respectively one)
element back onto stack a
*/
t_data	*sort_four_five(t_data *data)
{
	data = push(data, 'b');
	if (data->stack_a->size == 4)
		data = push(data, 'b');
	data = sort_three(data);
	data = insertion_sort(data);
	if (data->stack_b->size == 1)
		data = insertion_sort(data);
	data = rotate_sorted_list(data, 'a');
	return (data);
}
