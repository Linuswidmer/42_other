/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:33:00 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 16:43:48 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calc_cost_adjacent(t_elem *elem, int num)
{
	int	num_prev;
	int	num_next;

	num_prev = elem->prev->num;
	num_next = elem->num;
	if (num_prev < num && num < num_next)
		return (1);
	else
		return (0);
}

int	find_best_pos_b_rev_rotate(t_data *data, int rotations)
{
	t_elem	*tmp;
	t_elem	*tmp_b;
	int		i;
	int		num_rev_rotations_both;

	i = 0;
	tmp = data->stack_a->first;
	tmp_b = data->stack_b->first;
	while (i++ < rotations)
		tmp = tmp->prev;
	i = 0;
	num_rev_rotations_both = 0;
	while (i <= rotations)
	{
		if (calc_cost_adjacent(tmp_b, tmp->num) == 1)
		{
			num_rev_rotations_both = i;
			break ;
		}
		tmp_b = tmp_b->prev;
		i++;
	}
	data = apply_rev_rotations_both(data, num_rev_rotations_both);
	return (num_rev_rotations_both);
}

int	find_best_pos_b_rotate(t_data *data, int rotations)
{
	t_elem	*tmp;
	t_elem	*tmp_b;
	int		i;
	int		num_rotations_both;

	i = 0;
	tmp = data->stack_a->first;
	tmp_b = data->stack_b->first;
	while (i++ < rotations)
		tmp = tmp->next;
	i = 0;
	num_rotations_both = 0;
	while (i <= rotations)
	{
		if (calc_cost_adjacent(tmp_b, tmp->num) == 1)
		{
			num_rotations_both = i;
			break ;
		}
		tmp_b = tmp_b->next;
		i++;
	}
	data = apply_rotations_both(data, num_rotations_both);
	return (num_rotations_both);
}

t_data	*push_chunk_to_stack_b(t_data *data, int chunk_min, int chunk_max)
{
	int	i_r;
	int	i_rr;
	int	current_chunk_count;

	current_chunk_count = 0;
	while (current_chunk_count <= (chunk_max - chunk_min))
	{
		i_r = find_in_chunk_r(data->stack_a, chunk_min, chunk_max);
		i_rr = find_in_chunk_rr(data->stack_a, chunk_min, chunk_max);
		if (i_r <= i_rr)
		{
			if (data->stack_a->size > 0 && i_r > 0 && data->stack_b->size > 0)
				i_r = i_r - find_best_pos_b_rotate(data, i_r);
			data = apply_rotations(data, i_r, 'a');
		}
		else if (i_rr < i_r)
		{
			if (data->stack_a->size > 0 && i_rr > 0 && data->stack_b->size > 0)
				i_rr = i_rr - find_best_pos_b_rev_rotate(data, i_rr);
			data = apply_rev_rotations(data, i_rr, 'a');
		}
		data = push(data, 'b');
		current_chunk_count++;
	}
	return (data);
}

t_data	*chunk_sort(t_data *data)
{
	int	i;
	int	stack_size;
	int	num_chunks;
	int	chunk_lower_b;
	int	chunk_upper_b;

	i = 0;
	stack_size = data->stack_a->size;
	num_chunks = calc_chunk_size(stack_size);
	chunk_lower_b = 0;
	chunk_upper_b = (stack_size / num_chunks) - 1;
	while (i < (num_chunks - 1))
	{
		data = push_chunk_to_stack_b(data, chunk_lower_b, chunk_upper_b);
		chunk_lower_b = chunk_lower_b + stack_size / num_chunks;
		chunk_upper_b = chunk_upper_b + stack_size / num_chunks;
		i++;
	}
	data = push_chunk_to_stack_b(data, chunk_lower_b, chunk_upper_b - (3
				- stack_size % num_chunks));
	data = sort_three(data);
	while (data->stack_b->size > 0)
		data = find_in_stack_and_push(data, data->stack_b->size - 1);
	return (data);
}
