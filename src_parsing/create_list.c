/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:59:40 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/25 18:10:15 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void	process_first_token(t_lst **lst, t_parse *parse, int *i)
{
	(*lst) = malloc(sizeof(t_lst));
	(*lst)->prev = NULL;
	(*lst)->next = NULL;
	find_token(*lst, parse->args[*i], parse);
	(*lst)->cmd = strdup(parse->args[*i]);
	(*i)++;
}

void	process_remaining_tokens(t_lst **lst, t_parse *parse, int *i)
{
	while (parse->args[*i])
	{
		(*lst)->next = malloc(sizeof(t_lst));
		(*lst)->next->prev = (*lst);
		(*lst) = (*lst)->next;
		(*lst)->next = NULL;
		find_token(*lst, parse->args[*i], parse);
		(*lst)->cmd = strdup(parse->args[*i]);
		(*i)++;
	}
	(*lst)->next = NULL;
}

void	first_put_lst(t_lst **lst, t_parse *parse, t_command **node)
{
	t_lst	*first;
	int		i;

	i = 0;
	process_first_token(lst, parse, &i);
	first = (*lst);
	process_remaining_tokens(lst, parse, &i);
	(*lst) = first;
	print_list(*lst);
	check_pipe_start(lst, parse, node);
	if (parse->check != 1)
		check_chevron(lst, parse, node);
}
