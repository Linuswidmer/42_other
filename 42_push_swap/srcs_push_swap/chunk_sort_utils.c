/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:37:08 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 16:41:23 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_data	*find_in_stack_and_push(t_data *data, int find)
{
	int	i_rotate;
	int	i_rev_rotate;

	i_rotate = find_in_chunk_r(data->stack_b, find, find);
	i_rev_rotate = find_in_chunk_rr(data->stack_b, find, find);
	if (i_rotate <= i_rev_rotate)
		data = apply_rotations(data, i_rotate, 'b');
	else if (i_rev_rotate < i_rotate)
		data = apply_rev_rotations(data, i_rev_rotate, 'b');
	data = push(data, 'a');
	return (data);
}

/*
serches for the nect element in the range of chunk_min and chunk_max in stack
by rotating the stack
*/
int	find_in_chunk_r(t_stack *stack, int chunk_min, int chunk_max)
{
	int		stack_size;
	t_elem	*tmp;
	int		iterations;

	stack_size = stack->size;
	iterations = 0;
	tmp = stack->first;
	while (iterations < stack_size)
	{
		if (tmp->num >= chunk_min && tmp->num <= chunk_max)
			break ;
		iterations++;
		tmp = tmp->next;
	}
	return (iterations);
}

/*
serches for the nect element in the range of chunk_min and chunk_max in stack
by reverse rotating the stack
*/
int	find_in_chunk_rr(t_stack *stack, int chunk_min, int chunk_max)
{
	int		stack_size;
	t_elem	*tmp;
	int		iterations;

	iterations = 0;
	stack_size = stack->size;
	tmp = stack->first;
	while (iterations < stack_size)
	{
		if (tmp->num >= chunk_min && tmp->num <= chunk_max)
			break ;
		iterations++;
		tmp = tmp->prev;
	}
	return (iterations);
}
