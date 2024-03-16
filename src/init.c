/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 21:14:36 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/16 21:23:54 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// init retour du split args
t_parse	*init_t_parse(t_parse *parse)
{
	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->nb_blocks = 0;
	parse->args= NULL;
	parse->i = 0;
	parse->is_args = 0;
	return parse;
}

// Init la liste chainée
t_lst	*init_lst(t_lst *lst)
{
	lst = malloc(sizeof(t_lst));
	if (!lst)
		return NULL;
	lst->token = 0;
	lst->cmd = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	return lst;
}

// Init les nodes finales
t_node	*init_nodes(t_node *node)
{
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->nb_cmd_in_block = 0;
	node->file_in = NULL;
	node->file_out = NULL;
	node->prev = NULL;
	return (node);
}

