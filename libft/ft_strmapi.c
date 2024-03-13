/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:24:04 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/08 20:07:58 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*sm;
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	sm = malloc (sizeof(char) * ft_strlen(s) + 1);
	if (sm == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		sm[i] = s[i];
		i++;
	}
	sm[i] = '\0';
	i = 0;
	while (sm[i] != '\0')
	{
		sm[i] = f(i, sm[i]);
		i++;
	}
	return (sm);
}
