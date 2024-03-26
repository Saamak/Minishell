/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:34:04 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/18 18:20:39 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*csrc;
	unsigned char		*cdest;

	csrc = (unsigned char *) src;
	cdest = (unsigned char *) dest;
	if (src > dest)
		ft_memcpy(dest, src, n);
	else if (dest > src)
	{
		while (n--)
			cdest[n] = csrc[n];
	}
	return (cdest);
}
