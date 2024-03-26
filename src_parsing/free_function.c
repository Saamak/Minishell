/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:18:48 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/26 16:02:58 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void	free_tab(t_parse *parse) ////////////////////////
{
	int i;
	
	if (parse->args)
	{
		i = 0;
		while (parse->args[i])
		{
			free(parse->args[i]);
			i++;
		}
		free(parse->args);
	}
	if (parse)
		free(parse);
}

void	free_list(t_lst *lst) ////////////////////////
{
	t_lst *tmp;
	
	if (lst)
	{
		while (lst)
		{
			tmp = lst;
			lst = lst->next;
			if (tmp->cmd)
				free(tmp->cmd);
			free(tmp);
		}
	}
}

void	free_node(t_command **head)
{
	t_command	*current;

	current = (*head);
	while ((*head) != NULL)
	{
		(*head) = (*head)->next;
		free(current);
		current = (*head);
	}
}
