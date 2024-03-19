/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:13:21 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/19 13:43:54 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_node(t_lst **lst, t_node **node)
{

	t_lst	*first;
	t_node	*first_node;
	int		i;

	i = 0;
	if (lst == NULL || node == NULL)
		return;
	first = *lst;
	first_node = *node;
	(*node) = malloc(sizeof(t_node));
	(*node)->prev = NULL;
	(*node)->next = NULL;

	while ((*lst) != NULL)
	{
		if((*lst)->token == CMD)
		{
			(*node)->nb_cmd_in_block++;
			printf("\nCurrent CMD : [ %s%s%s ]\n"RESET, Y, (*lst)->cmd, RESET);
			(*node)->file_in = infile_before(*lst);
			if(ft_strcmp((*node)->file_in, "STDIN") == 0)
				(*node)->file_in = infile_after(*lst);

			(*node)->file_out = is_outfile_before(*lst);
			if(ft_strcmp((*node)->file_out, "STDOUT") == 0)
				(*node)->file_out = is_outfile_after(*lst);
			if (ft_strcmp((*node)->file_out, "STDOUT") != 0)
			{
				printf(Y"\nCUTTING BLOCK1\n"RESET);
				(*node)->next = malloc(sizeof(t_node));
				(*node)->next->prev = *node;
				(*node) = (*node)->next;
				(*node)->next = NULL;
			}
			else if((*lst)->next != NULL && ((*lst)->next) && in_next_cmd((*lst)->next))
			{
				printf(Y"\nCUTTING BLOCK\n"RESET);
			}
			else if(((*lst)->next != NULL && out_next_cmd((*lst)->next)))
			{
				printf(Y"\nCUTTING BLOCK\n"RESET);
				(*node)->file_out = out_next_cmd(*lst);
				break;
			}
			printf("INFILE! : %s\n", (*node)->file_in);
			// (*node)->cmd[i][0] = (*lst)->cmd;
			// printf("CMD : %s\n", (*node)->cmd[i][0]);
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
		if (tmp->token == PIPE)
			break;
		if (tmp->token == INFILE)
		{
			printf(G"Found INFILE token Before CMD  : %s\n"RESET, tmp->cmd);  // Print the command associated with the INFILE token
			return (tmp->cmd);
		}
		tmp = tmp->prev;
	}
	printf(R"No INFILE token found before CMD token\n"RESET);
	return ("STDIN");
}

char	*infile_after(t_lst *lst)
{
	t_lst	*tmp;
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			break;
		if (tmp->token == INFILE)
		{
			printf(G"Found INFILE token After CMD  : %s\n"RESET, tmp->cmd);
			return (tmp->cmd);
		}
		tmp = tmp->next;
	}
	printf(R"No INFILE token found after CMD token\n"RESET);
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
		{
			printf(G"Found OUTFILE token Before CMD  : %s\n"RESET, tmp->cmd);
			return (tmp->cmd);
		}
		tmp = tmp->prev;
	}
	printf(R"No OUTFILE token found before CMD token\n"RESET);
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
		{
			printf(G"Found OUTFILE token After CMD  : %s\n"RESET, tmp->cmd);
			file = tmp->cmd;
		}
		if ((tmp->token == PIPE && tmp->next->token == CMD) || tmp->next == NULL)
			return (file);
		tmp = tmp->next;
	}
	printf(R"No OUTFILE token found after CMD token\n"RESET);
	return ("STDOUT");
}

int	in_next_cmd(t_lst *lst)
{
	printf(Y"\nINChecking Next Command\n"RESET);
	t_lst	*tmp;
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token == CMD)
 		{
				if (ft_strcmp(infile_before(tmp), "STDIN") != 0 || ft_strcmp(infile_after(tmp), "STDIN") != 0)
					return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char *out_next_cmd(t_lst *lst)
{
	printf(Y"\nOUTChecking Next Command\n"RESET);
	t_lst	*tmp;
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token == CMD)
 		{
				if (ft_strcmp(is_outfile_before(tmp), "STDOUT") != 0)
					return (is_outfile_before(tmp));
				if (ft_strcmp(is_outfile_after(tmp), "STDOUT") != 0)
					return (is_outfile_after(tmp));
		}
		tmp = tmp->next;
	}
	return ("STDOUT");
}

// int	next_cmd_exists(t_lst *lst)
// {
// 	t_lst	*tmp;
// 	tmp = lst;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->token == CMD)
// 		{
// 			if (tmp->next->token == CMD)
// 			{
// 				printf(Y"\nNext CMD Exists\n"RESET);
// 				return (1);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
