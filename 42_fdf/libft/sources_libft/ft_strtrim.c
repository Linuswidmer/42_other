/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:16:17 by lwidmer           #+#    #+#             */
/*   Updated: 2022/12/15 10:22:09 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	trim_beginning(char const *s1, char const *set)
{
	size_t	j;
	size_t	beginning;

	j = 0;
	beginning = 0;
	while (beginning < ft_strlen(s1))
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (ft_strncmp((s1 + beginning), (set + j), 1) == 0)
			{
				beginning++;
				break ;
			}
			else
				j++;
		}
		if (j == ft_strlen(set))
			break ;
	}
	return (beginning);
}

size_t	trim_end(char const*s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	end;

	i = 0;
	end = ft_strlen(s1) - 1;
	while (end > 0)
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (ft_strncmp((s1 + end), (set + j), 1) == 0)
			{
				end--;
				i++;
				break ;
			}
			else
				j++;
		}
		if (j == ft_strlen(set))
			break ;
	}
	return (ft_strlen(s1) - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	beginning;
	size_t	end;

	beginning = trim_beginning(s1, set);
	end = trim_end(s1, set);
	ptr = ft_substr(s1, beginning, end - beginning);
	return (ptr);
}
