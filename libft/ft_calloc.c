/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:58 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/18 18:20:39 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*p;
	size_t		sizemax;

	sizemax = nmemb * size;
	if (size <= 0 || nmemb <= 0)
		return (malloc(1));
	if ((int)size < 0 || (int)nmemb < 0)
		return (NULL);
	if (size == 0 || nmemb == 0)
		return (malloc(1));
	p = malloc(sizemax);
	if (!p)
		return (NULL);
	if (p != NULL)
	{
		ft_bzero(p, sizemax);
	}
	return (p);
}
