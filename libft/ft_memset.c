/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:08:08 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/02 18:44:14 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*copy;
	size_t			i;

	i = 0;
	copy = ((unsigned char *)s);
	while (i < n)
	{
		copy[i] = ((unsigned char) c);
		i ++;
	}
	return (s);
}
