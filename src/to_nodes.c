/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:13:21 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/16 22:14:53 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_node(t_lst **lst, t_node **node)
{

	t_lst	*first;
	t_node	*first_node;


	first = *lst;
	first_node = *node;

	while ((*lst) != NULL)
	{
		if((*lst)->token == CMD)
		{
			(*node)->next = NULL;
			(*node)->file_in = infile_before(*lst);  // chercher outfile avant et apres, jarrete de chercher outfile si pipe ou fin de ligne
			if(ft_strcmp((*node)->file_in, "STDIN") == 0)
				(*node)->file_in = infile_after(*lst);
			(*node)->file_out = is_outfile_before(*lst);
			(*node)->file_out = is_outfile_after(*lst);
			(*node)->nb_cmd_in_block++;
			(*node)->prev = *node;
			if((*node)->prev->file_out != NULL && (*node)->prev->file_out != (*node)->file_out)
			{
				(*node)->next = malloc(sizeof(t_node));
				(*node) = (*node)->next;
			}
		}
		*lst = (*lst)->next;
	}
	*lst = first;
	*node = first_node;
}

char *infile_before(t_lst *lst)
{
    t_lst	*tmp;
    tmp = lst;
    while (tmp->prev != NULL)
    {
        printf("Current token: %d\n", tmp->token);  // Print the current token
        if (tmp->token == INFILE)
        {
            printf("Found INFILE token: %s\n", tmp->cmd);  // Print the command associated with the INFILE token
            return (tmp->cmd);
        }
        tmp = tmp->prev;
    }
    printf("No INFILE token found before CMD token\n");
    return ("STDIN");
}

char	*infile_after(t_lst *lst)
{
	t_lst	*tmp;
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token == INFILE)
			return (tmp->cmd);
		tmp = tmp->next;
	}
	return ("STDIN");
}

char	*is_outfile_before(t_lst *lst)
{
	t_lst	*tmp;
	tmp = lst;
	while (tmp->prev != NULL)
	{
		if (tmp->token == PIPE)
			break;
		if (tmp->token == OUTFILE)
			return (tmp->cmd);
		tmp = tmp->prev;
	}
	return ("STDOUT");
}

char	*is_outfile_after(t_lst *lst)
{
	t_lst	*tmp;
	tmp = lst;
	char	*file;
	file = "STDOUT";
	while (tmp != NULL)
	{
		if(tmp->token == OUTFILE)
			file = tmp->cmd;
		if ((tmp->token == PIPE && tmp->next->token == CMD) || tmp->next == NULL)
			return (file);
		tmp = tmp->next;
	}
	return ("STDOUT");
}
