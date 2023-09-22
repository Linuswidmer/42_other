/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 09:58:53 by lwidmer           #+#    #+#             */
/*   Updated: 2022/12/15 11:40:11 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	size_t	i;

	temp = NULL;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (((char *)s)[i] == (char)c)
			temp = (char *)s + i;
		i++;
	}
	return (temp);
}
