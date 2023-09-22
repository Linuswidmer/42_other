/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:15:45 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:40:59 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
The functions in this file implement the concept of swapping. Swapping means
changing the positions of the first and the second element in a stack.
Since we are working with a double linked circular list, we have to take care
that we connect all neighbours correctly, update the entry of the stack and
need different swapping functions for different stack sizes.
*/

static t_elem	*swap_stack_size_two(t_elem *first)
{
	t_elem	*second;

	second = first->next;
	first->next = second;
	second->prev = first;
	second->next = first;
	first->prev = second;
	return (second);
}

static t_elem	*swap_stack_size_bigger_two(t_elem *first)
{
	t_elem	*tmp;
	t_elem	*second;

	second = first->next;
	tmp = first->prev;
	tmp->next = second;
	second->prev = tmp;
	tmp = second->next;
	first->next = tmp;
	tmp->prev = first;
	second->next = first;
	first->prev = second;
	return (second);
}

t_data	*swap(t_data *data, char which)
{
	ft_printf("s%c\n", which);
	if ((which == 'a' || which == 's') && data->stack_a->first)
	{
		if (data->stack_a->size == 2)
			data->stack_a->first = swap_stack_size_two(data->stack_a->first);
		else if (data->stack_a->size > 2)
			data->stack_a->first
				= swap_stack_size_bigger_two(data->stack_a->first);
	}
	if ((which == 'b' || which == 's') && data->stack_b)
	{
		if (data->stack_b->size == 2)
			data->stack_b->first = swap_stack_size_two(data->stack_b->first);
		else if (data->stack_b->size > 2)
			data->stack_b->first
				= swap_stack_size_bigger_two(data->stack_b->first);
	}
	return (data);
}

t_data	*swap_both(t_data *data)
{
	if (data)
		data = swap(data, 's');
	return (data);
}
