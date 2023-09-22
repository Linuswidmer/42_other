/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 09:42:26 by lwidmer           #+#    #+#             */
/*   Updated: 2022/12/22 09:43:01 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_intlen_base(long int n, unsigned int baselen)
{
	unsigned int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > (baselen - 1))
	{
		i++;
		n = n / baselen;
	}
	return (i + 1);
}
