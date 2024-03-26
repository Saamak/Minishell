/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 21:14:36 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/26 15:34:36 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

// init retour du split args
t_parse	*init_t_parse(t_parse *parse)
{
	parse = calloc(1 ,sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->nb_blocks = 0;
	parse->args = NULL;
	parse->i = 0;
	parse->is_args = 0;
	parse->check = 0;
	parse->nb_out_to_create = 0;
	return (parse);
}

// Init la liste chainée
t_lst	*init_lst(t_lst *lst)
{
	lst = calloc(1 ,sizeof(t_lst));
	if (!lst)
		return (NULL);
	lst->token = 0;
	lst->cmd = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

// Init les nodes finales
t_command	*init_nodes(t_command *node)
{
	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->nb_cmd_in_block = 0;
	node->file_in = NULL;
	node->file_out = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->cmd_args = NULL;
	node->to_create = NULL;
	node->heredoc_text = NULL;
	node->append = 0;
	return (node);
}
