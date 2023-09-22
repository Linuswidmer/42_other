/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:27:36 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:39:05 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Returns the size of the stack, which is the number of elements in the array;
*/
int	calc_stack_size(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
		i++;
	return (i);
}

/*
cerates a new array with the same number of elements, as the input array to
calculate a consistent index of numbers. To do so, for each number the array
is iterated in a search for smaller numbers than the current number, which
results in the index
*/
int	*calc_data_index(t_data *data)
{
	int	*arr;
	int	i;
	int	j;
	int	index;

	arr = malloc(sizeof(int) * data->stack_a->size);
	if (!arr)
		terminate_on_error(data);
	i = 0;
	while (i < data->stack_a->size)
	{
		j = 0;
		index = 0;
		while (j < data->stack_a->size)
		{
			if (ft_atoi(data->split_arr[i]) > ft_atoi(data->split_arr[j]))
				index++;
			j++;
		}
		arr[i] = index;
		i++;
	}
	return (arr);
}

t_elem	*new_elem(int num)
{
	t_elem	*element;

	element = malloc(sizeof(t_elem));
	if (!element)
		return (NULL);
	element->num = num;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}

/*
is called when there is more than one element and iteratively creates a new
element with the corresponding value, that is then connected with its previous
and subsequent neighbour of the stack.
After all elements have been created, it connects the beginning of the stack to
the end of the stack, creating a double linked circular list.
*/
static void	split_arr_loop(t_data *data, int *index_arr, t_elem *tmp)
{
	int		i;
	t_elem	*tmp_2;

	i = 2;
	while (data->split_arr[i])
	{
		tmp_2 = new_elem(index_arr[i]);
		if (!tmp_2)
		{
			free(index_arr);
			terminate_on_error(data);
		}
		tmp->next = tmp_2;
		tmp_2->prev = tmp;
		tmp = tmp_2;
		i++;
	}
	tmp->next = data->stack_a->first;
	data->stack_a->first->prev = tmp;
}

/*
Initializes the first element of the stack and if size is bigger than one
calls the iterative process 'split_arr_loop', which will create all following
elements.
*/
void	split_arr_to_stack_a(t_data *data, int *index_arr)
{
	t_elem	*tmp;

	data->stack_a->first = new_elem(index_arr[0]);
	if (!data->stack_a->first)
	{
		free(index_arr);
		terminate_on_error(data);
	}
	if (data->stack_a->size > 1)
	{
		tmp = new_elem(index_arr[1]);
		if (!tmp)
		{
			free(index_arr);
			terminate_on_error(data);
		}
		data->stack_a->first->next = tmp;
		tmp->prev = data->stack_a->first;
		split_arr_loop(data, index_arr, tmp);
	}
	else
	{
		data->stack_a->first->prev = data->stack_a->first;
		data->stack_a->first->next = data->stack_a->first;
	}
}
