/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:42 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:29:35 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
The following functions implement the concept of rotation and reverse
rotation. Since we are working with a double linked list, we can simply
us the 'next' and 'prev' attributes of our elements to move back and forth.
*/

t_data	*rotate(t_data *data, char which)
{
	if ((which == 'a' || which == 'r') && data->stack_a->first)
		data->stack_a->first = data->stack_a->first->next;
	if ((which == 'b' || which == 'r') && data->stack_b->first)
		data->stack_b->first = data->stack_b->first->next;
	ft_printf("r%c\n", which);
	return (data);
}

t_data	*rev_rotate(t_data *data, char which)
{
	if ((which == 'a' || which == 'r') && data->stack_a->first)
		data->stack_a->first = data->stack_a->first->prev;
	if ((which == 'b' || which == 'r') && data->stack_b->first)
		data->stack_b->first = data->stack_b->first->prev;
	ft_printf("rr%c\n", which);
	return (data);
}

t_data	*rotate_both(t_data *data)
{
	if (data)
		data = rotate(data, 'r');
	return (data);
}

t_data	*rev_rotate_both(t_data *data)
{
	if (data)
		data = rev_rotate(data, 'r');
	return (data);
}
