/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:52:13 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:16:56 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Can print the initial array of integers that is created before stacks
are populated.
*/
void	print_arr_index(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%i   ", arr[i]);
		i++;
	}
	ft_printf("\n");
}

/*
Prints each number of the stack and their neighbours (important to check
whether the double linked list was successful)
*/
void	print_stack(t_stack *stack)
{
	int		i;
	int		size;
	t_elem	*elem;

	size = stack->size;
	i = 0;
	elem = stack->first;
	ft_printf("First List elem is %p\n", elem);
	while (i < size)
	{
		ft_printf("Value is %i,     Previous is %i,    Next is %i\n",
			elem->num, elem->prev->num, elem->next->num);
		elem = elem->next;
		i++;
	}
}
