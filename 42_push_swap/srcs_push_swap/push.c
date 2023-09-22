/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:24:20 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:25:00 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Each function here is related to the concept of pushing the top element
of one stack onto the top of the other stack.
Since we are working with a double linked list, we have to take care of
correctly connecting the neighbours when pushing from one stack to another
and need seperate functions for stack sizes zero, one and bigger than one

all follwing functions use the keyword 'from' for the stack from which an
element is pushed and 'to' to which the element is pushed.
*/

/*
helper function, updating the entry elements of the stacks (first)
*/
static t_data	*stack_first(t_data *data, t_elem *from,
	t_elem *new_beginning_from, t_elem *new_beginning_to)
{
	if (from == data->stack_a->first)
	{
		data->stack_b->first = new_beginning_to;
		data->stack_a->first = new_beginning_from;
	}
	else
	{
		data->stack_a->first = new_beginning_to;
		data->stack_b->first = new_beginning_from;
	}
	return (data);
}

/*
is called when the stack to which an element is pushed has no elements yet
(size is zero)
*/
static t_data	*size_zero(t_data *data, t_elem *from)
{
	t_elem	*zero_from;
	t_elem	*second_from;
	t_elem	*new_beginning_to;

	new_beginning_to = new_elem(from->num);
	if (!new_beginning_to)
		terminate_on_error(data);
	new_beginning_to->next = new_beginning_to;
	new_beginning_to->prev = new_beginning_to;
	if (from == from->prev)
		second_from = NULL;
	else
	{
		zero_from = from->prev;
		second_from = from->next;
		zero_from->next = second_from;
		second_from->prev = zero_from;
	}
	data = stack_first(data, from, second_from, new_beginning_to);
	free(from);
	return (data);
}

/*
is called when the stack to which an element is pushed has only one element
(size is one)
*/
static t_data	*size_one(t_data *data, t_elem *from, t_elem *to)
{
	t_elem	*zero_from;
	t_elem	*second_from;
	t_elem	*new_beginning_to;

	new_beginning_to = new_elem(from->num);
	if (!new_beginning_to)
		terminate_on_error(data);
	new_beginning_to->prev = to;
	new_beginning_to->next = to;
	to->next = new_beginning_to;
	to->prev = new_beginning_to;
	if (from == from->prev)
		second_from = NULL;
	else
	{
		zero_from = from->prev;
		second_from = from->next;
		zero_from->next = second_from;
		second_from->prev = zero_from;
	}
	data = stack_first(data, from, second_from, new_beginning_to);
	free(from);
	return (data);
}

/*
is called when the stack to which an element is pushed has more than one
elements (size is bigger than one)
*/
static t_data	*bigger_one(t_data *data, t_elem *from, t_elem *to)
{
	t_elem	*zero_from;
	t_elem	*second_from;
	t_elem	*zero_to;
	t_elem	*new_beginning_to;

	zero_to = to->prev;
	new_beginning_to = new_elem(from->num);
	if (!new_beginning_to)
		terminate_on_error(data);
	new_beginning_to->prev = zero_to;
	new_beginning_to->next = to;
	zero_to->next = new_beginning_to;
	to->prev = new_beginning_to;
	if (from == from->next)
		second_from = NULL;
	else
	{
		second_from = from->next;
		zero_from = from->prev;
		zero_from->next = second_from;
		second_from->prev = zero_from;
	}
	data = stack_first(data, from, second_from, new_beginning_to);
	free(from);
	return (data);
}

/*
'Wrapping function', deciding from which stack should the element be pushed
and calling the according function concatenating the new ends of the stacks
based on the size of the stacks
*/
t_data	*push(t_data *data, char which)
{
	ft_printf("p%c\n", which);
	if (which == 'b' && data->stack_a->first)
	{
		if (data->stack_b->size == 0)
			data = size_zero(data, data->stack_a->first);
		else if (data->stack_b->size == 1)
			data = size_one(data, data->stack_a->first, data->stack_b->first);
		else
			data = bigger_one(data, data->stack_a->first, data->stack_b->first);
		data->stack_a->size = data->stack_a->size - 1;
		data->stack_b->size = data->stack_b->size + 1;
	}	
	else if (which == 'a' && data->stack_b->first)
	{
		if (data->stack_a->size == 0)
			data = size_zero(data, data->stack_b->first);
		else if (data->stack_a->size == 1)
			data = size_one(data, data->stack_b->first, data->stack_a->first);
		else
			data = bigger_one(data, data->stack_b->first, data->stack_a->first);
		data->stack_a->size = data->stack_a->size + 1;
		data->stack_b->size = data->stack_b->size - 1;
	}
	return (data);
}
