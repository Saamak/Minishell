/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:54:10 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/13 15:06:30 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Affiche le double tableau splitting
void	print_parse(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse->args[i])
	{
		printf("args[%d] : %s\n", i, parse->args[i]);
		i++;
	}
}

// Affiche la liste chainée
void	print_list(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		printf("Node [%d] : %s%s     %s| token :   %s%s\n\n"RESET, i, G,  tmp->cmd, RESET, Y, get_token_name(tmp->token));
		tmp = tmp->next;
		i++;
	}
	printf("END\n");
}

void	print_list2(t_node *node)
{
	if (node->file_in || node->file_out)
	{
		printf("file_in : %s\n", node->file_in);
		printf("file_out : %s\n", node->file_out);
	}
}

const char	*get_token_name(int token)
{
	switch (token)
	{
		case PIPE: return "PIPE";
		case CHEVRON_IN: return "CHEVRON_IN";
		case CHEVRON_OUT: return "CHEVRON_OUT";
		case CMD: return "CMD";
		case INFILE: return "INFILE";
		case OUTFILE: return "OUTFILE";
		case ARGS: return "ARGS";
		default: return "UNKNOWN";
	}
}
