/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:53:37 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/07 22:01:49 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	stlen(long int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			n_len;
	int			i;
	long int	h;
	long int	l;

	h = n;
	n_len = stlen(n);
	i = n_len;
	l = n;
	result = malloc (sizeof(char) * n_len + 1);
	if (result == 0)
		return (0);
	if (l < 0)
		l = l * -1;
	result[i] = '\0';
	i--;
	while (i >= 0)
	{
		result[i--] = l % 10 + '0';
		l = l / 10;
	}
	if (h < 0)
		result[0] = '-';
	return (result);
}
