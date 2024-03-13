/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:29:24 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/06 15:23:43 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;
	unsigned char	cc;

	cc = (unsigned char)c;
	i = 0;
	cs = (unsigned char *)s;
	while (i < n)
	{
		if (cs[i] == cc)
			return (cs + i);
		i++;
	}
	return (NULL);
}
