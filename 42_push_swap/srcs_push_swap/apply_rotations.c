/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_rotations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:04:12 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:06:56 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_data	*apply_rotations(t_data *data, int rotations, char which)
{
	while (rotations)
	{
		data = rotate(data, which);
		rotations--;
	}
	return (data);
}

t_data	*apply_rotations_both(t_data *data, int rotations)
{
	while (rotations)
	{
		data = rotate_both(data);
		rotations--;
	}
	return (data);
}

t_data	*apply_rev_rotations(t_data *data, int rev_rotations, char which)
{
	while (rev_rotations)
	{
		data = rev_rotate(data, which);
		rev_rotations--;
	}
	return (data);
}

t_data	*apply_rev_rotations_both(t_data *data, int rev_rotations)
{
	while (rev_rotations)
	{
		data = rev_rotate_both(data);
		rev_rotations--;
	}
	return (data);
}
