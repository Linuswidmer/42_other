/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:09:10 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:12:39 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
initializes an empty stack
*/
static t_stack	*init_stack_struct(t_data *data)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		terminate_on_error(data);
	stack->size = 0;
	return (stack);
}

/*
initiallizing an empty data container, which will hold both stacks, as well 
as the array of integers from processing
*/
static t_data	*init_data_struct(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		terminate_on_error(NULL);
	data->split_arr = NULL;
	data->stack_a = init_stack_struct(data);
	data->stack_b = init_stack_struct(data);
	return (data);
}

t_data	*init(int argc, char **argv)
{
	t_data	*data;

	data = init_data_struct();
	process_input(data, argv, argc);
	return (data);
}
