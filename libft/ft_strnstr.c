/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:53:20 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/08 19:55:00 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	int		len_tof;

	len_tof = 0;
	j = 0;
	i = 0;
	if (len == 0 && big == 0)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	while (little[len_tof] != '\0')
		len_tof++;
	while (big[i] != '\0' && i < len)
	{
		while (big[i + j] == little[j] && (i + j) < len)
		{
			j++;
			if (j == len_tof)
				return ((char *)big + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
