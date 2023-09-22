/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:44:29 by lwidmer           #+#    #+#             */
/*   Updated: 2022/12/16 11:07:13 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print(unsigned int nb, int fd)
{
	char	printchar;

	if (nb != 0)
	{
		print(nb / 10, fd);
		printchar = (nb % 10) + '0';
		write(fd, &printchar, 1);
	}
}

void	ft_putnbr_fd(int nb, int fd)
{
	size_t	num;

	if (nb < 0)
	{
		write(fd, "-", 1);
		num = nb * (-1);
		print(num, fd);
	}
	else if (nb == 0)
		write(fd, "0", 1);
	else
		print(nb, fd);
}
