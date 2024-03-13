/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:18:48 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/13 15:02:32 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse->args[i])
	{
		free(parse->args[i]);
		parse->args[i] = NULL;
		i++;
	}
	free(parse->args);
	parse->args = NULL;
}

void	free_list(t_lst **head)
{
	t_lst	*current;

	current = (*head);
	while ((*head) != NULL)
	{
		// printf("freeing %s\n", (*head)->cmd);
		(*head) = (*head)->next;
		free(current);
		current = (*head);
	}
}
