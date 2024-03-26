/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:54:10 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/25 18:12:30 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

// Affiche le double tableau splitting
// void	print_parse(t_parse *parse)
// {
// 	int	i;

// 	i = 0;
// 	while (parse->args[i])
// 	{
// 		printf("args[%d] : %s\n", i, parse->args[i]);
// 		i++;
// 	}
// }

// Affiche la liste chainée
void	print_list(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		//printf("Node [%d] : %s%s     %s| token :   %s%s\n\n"RESET, i, G,  tmp->cmd, RESET, Y, get_token_name(tmp->token));
		tmp = tmp->next;
		i++;
	}
}

// void	print_node(t_command *node)
// {
// 	t_command	*tmp;
// 	int		i;
// 	int		j;
// 	int k;

// 	i = 0;
// 	tmp = node;
// 	while (tmp != NULL)
// 	{
// 		k = 0;
// 		j = 0;
// 		// while(tmp->cmd_args[k] != NULL)
// 		// {
// 		// 	while(tmp->cmd_args[k][j] != NULL)
// 		// 	{
// 		// 		printf("CMD_ARGS[%d] : %s\n", j, tmp->cmd_args[k][j]);
// 		// 		j++;
// 		// 	}
// 		// 	k++;
// 		// }
// 		// j = 0;
// 		// while(tmp->to_create != NULL)
// 		// {
// 		// 	printf("TO_CREATE[%d] : %s\n", j, tmp->to_create[j]);
// 		// 	j++;
// 		// }
// 		tmp = tmp->next;
// 		i++;
// 	}
// }

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
		case HEREDOC: return "HEREDOC";
		case APPEND: return "APPEND";
		default: return "UNKNOWN";
	}
}

char	*get_token_char(int token)
{
	switch (token)
	{
		case PIPE: return "|";
		case CHEVRON_IN: return "newline";
		case CHEVRON_OUT: return "newline";
		case CMD: return "CMD";
		case INFILE: return "INFILE";
		case OUTFILE: return "OUTFILE";
		case ARGS: return "ARGS";
		case HEREDOC: return "newline";
		default: return "UNKNOWN";
	}
}
