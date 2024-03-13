/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:58 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/13 16:47:22 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
