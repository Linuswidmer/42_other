/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:16:59 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/11 10:37:06 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
tests if numbers passed to push_swap program are in the range of MIN_INT 
and MAX_INT by iterating through the array
*/
int	check_min_and_max_int(char **split_arr)
{
	int			i;
	long int	num;

	i = 0;
	while (split_arr[i])
	{
		num = ft_atoi(split_arr[i]);
		if (num < -2147483648 || num > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

/*
checks whether all numbers that are to be sorted are unique, by comparing
each number with all following numbers in the array
*/
int	check_if_no_doubles(char **split_arr)
{
	int	i;
	int	j;

	i = 0;
	while (split_arr[i])
	{
		j = i + 1;
		while (split_arr[j])
		{
			if (ft_atoi(split_arr[i]) == ft_atoi(split_arr[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*
checks whether only digits are passed to the program, a negative sign is
valid if it is on position zero and not followed by the nullbyte.
*/
int	check_if_input_numeric(char **split_arr)
{
	int	i;
	int	j;

	i = 0;
	while (split_arr[i])
	{
		j = 0;
		while (split_arr[i][j] != '\0')
		{
			if (ft_isdigit(split_arr[i][j]) != 0)
				j++;
			else if (j == 0 && split_arr[i][j] == '-' &&
				split_arr[i][j + 1] != '\0')
			{
				j++;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

/*
applies the three input checks above subsequently. Returns 0 if any of them fails
*/
int	check_input(char **split_arr)
{
	if (check_if_input_numeric(split_arr) == 0)
		return (0);
	if (check_if_no_doubles(split_arr) == 0)
		return (0);
	if (check_min_and_max_int(split_arr) == 0)
		return (0);
	return (1);
}
