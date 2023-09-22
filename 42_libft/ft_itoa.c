/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:33:29 by lwidmer           #+#    #+#             */
/*   Updated: 2022/12/15 10:58:57 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numdigits(int n)
{
	int	i;

	i = 0;
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	return (i + 1);
}

void	ft_putinttostr(char *s, int n, int len, int neg)
{
	int	i;
	int	j;
	int	base;

	i = neg;
	j = 1;
	base = 10;
	if (len == 1)
	{
		s[i] = n + '0';
		len--;
	}
	while (j < len - 1)
	{
		base = base * 10;
		j++;
	}
	while (len)
	{
		s[i] = n / base % 10 + '0';
		len--;
		base = base / 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		neg;

	len = 0;
	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		neg = 1;
		n = n * -1;
	}
	len = ft_numdigits(n);
	ptr = malloc(len + neg + 1);
	if (ptr)
	{
		if (neg == 1)
			ptr[0] = '-';
		ft_putinttostr(ptr, n, len, neg);
		ptr[len + neg] = '\0';
	}
	return (ptr);
}
