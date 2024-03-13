/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:34:04 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/04 21:34:08 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
