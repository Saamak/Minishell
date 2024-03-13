/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:51:51 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/10 17:17:06 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*st1;

	st1 = malloc(sizeof(t_list));
	if (st1 == NULL)
		return (NULL);
	st1->content = content;
	st1->next = NULL;
	return (st1);
}

