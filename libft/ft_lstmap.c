/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:16:22 by ppitzini          #+#    #+#             */
/*   Updated: 2023/11/13 16:09:46 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list2;
	t_list	*node;

	list2 = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
			ft_lstclear(&list2, del);
		ft_lstadd_back(&list2, node);
		lst = lst->next;
	}
	return (list2);
}
