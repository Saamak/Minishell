/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:48:36 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/05 18:55:21 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			write(fd, "-2147483648", 11);
		}
		else
		{
			nb = nb * -1;
			write(fd, "-", 1);
		}
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else if (nb >= 0 && nb <= 9)
		ft_putchar_fd(nb + '0', fd);
}
