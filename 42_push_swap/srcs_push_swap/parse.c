/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:00:29 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/09 15:14:53 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
splits a space separated string into a 2 dimensional array of characters
*/
void	process_input_one_arg(t_data *data, char **argv)
{
	data->split_arr = ft_split(argv[1], ' ');
	if (!data->split_arr || !data->split_arr[0])
		terminate_on_error(data);
}

/*
creates a 2 dimensional array of characters containing the input to the
program, by processing each argument individually
*/
void	process_input_multiple_arg(t_data *data, char **argv, int argc)
{
	int	i;

	i = 1;
	data->split_arr = malloc(sizeof(char *) * argc);
	if (!data->split_arr)
		terminate_on_error(data);
	while (i < argc)
	{
		data->split_arr[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	data->split_arr[i - 1] = NULL;
}

/* 
based on the number of arguments to the program, decides whether
input is a single string with space seperation or each argument to the program 
is a digit.
Calls the check_input fuction and on success calculates the stack size, 
calculates the data index and populates the input to stack a
*/
void	process_input(t_data *data, char **argv, int argc)
{
	int	*arr;

	if (argc == 2)
		process_input_one_arg(data, argv);
	else
		process_input_multiple_arg(data, argv, argc);
	if (check_input(data->split_arr))
	{
		data->stack_a->size = calc_stack_size(data->split_arr);
		data->max_value = data->stack_a->size - 1;
		arr = calc_data_index(data);
		split_arr_to_stack_a(data, arr);
		free(arr);
	}
	else
		terminate_on_error(data);
}
