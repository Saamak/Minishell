/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:32:23 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/05 17:10:19 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*a;
	unsigned char	cc;

	cc = c;
	a = (char *)s;
	i = 0;
	while (a[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (a[i] == cc)
			return (a + i);
		i--;
	}
	return (0);
}
