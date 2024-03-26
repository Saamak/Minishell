/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:51:57 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/18 18:20:39 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	copy = malloc(1 + len * sizeof(char));
	if (copy == 0)
		return (0);
	while (s[i] != '\0')
	{
		copy[j] = s[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
