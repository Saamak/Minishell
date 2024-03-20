/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:13:21 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/20 20:21:19 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void triple_handle(t_lst **lst, t_node **node)
{
	int i;
	int j;

	(*node)->cmd_args = malloc(sizeof(char***) * ((*node)->nb_cmd_in_block + 1));

	i = 0;
	while (i < (*node)->nb_cmd_in_block)
	{
		j = 0;
		(*node)->cmd_args[i] = malloc(sizeof(char**) * 1);
		if ((*lst)->token == CMD)
		{
			(*node)->cmd_args[i][j] = strdup((*lst)->cmd);
			*lst = (*lst)->next;
			j++;
			while ((*lst)->token == ARGS)
			{
				char **temp = malloc(sizeof(char**) * (j + 1));
				int k = 0;
				while(k < j)
				{
					temp[k] = (*node)->cmd_args[i][k];
					k++;
				}
				temp[j] = strdup((*lst)->cmd);
				free((*node)->cmd_args[i]);
				(*node)->cmd_args[i] = temp;
				j++;
				*lst = (*lst)->next;
			}
			(*node)->cmd_args[i][j] = NULL;
			i++;
		}
		if (i != (*node)->nb_cmd_in_block)
			*lst = (*lst)->next;
	}
	(*node)->cmd_args[i] = NULL;
	while (((*lst) != NULL) && (*lst)->token != PIPE)
		(*lst) = (*lst)->next;
	// (*lst)->prev = NULL;
}

void print_triple(t_node **node)
{
	int i;
	int j;

	i = 0;
	while ((*node)->cmd_args[i])
	{
		j = 0;
		while ((*node)->cmd_args[i][j])
		{
			printf("tab[%d][%d] :%s\n", i, j, (*node)->cmd_args[i][j]);
			j++;
		}
		i++;
	}
	return ;
}

void	to_node(t_lst **lst, t_node **node)
{

	t_lst	*first;
	t_node	*first_node;

	if (lst == NULL || node == NULL)
		return;
	first = *lst;
	(*node) = malloc(sizeof(t_node));
	first_node = *node;
	(*node)->prev = NULL;
	(*node)->next = NULL;

	while ((*lst) != NULL)
	{
		if((*lst)->token == CMD) // FIND NEXT COMMAND
		{
			//////////////////////////TRAITEMENT BLOCK////////////////////////////
			(*node)->file_in = infile_after(*lst);
			if (!(*node)->file_in)
				(*node)->file_in = infile_before(*lst);
			(*node)->file_out = is_outfile_after(*lst, *node);
			if(!((*node)->file_out))
				(*node)->file_out = is_outfile_before(*lst);

			//////////////////////////CREATION TRIPLE//////////////////////////////////////////////
			triple_handle(lst, node);
			///////////////////////////PRINT TRIPLE/////////////////////////////////////////////////
			printf(G"PRINT_CMD_IN_BLOCK\n"RESET);
			print_triple(node);
		}
		if ((*lst) != NULL)
		{
			(*lst) = (*lst)->next;
			printf("lst->cmd : %s\n", (*lst)->cmd);
			(*node)->next = malloc(sizeof(t_node)); ////////CREATE NODE/////////////////
			(*node)->next->prev = *node;
			(*node) = (*node)->next;
			(*node)->next = NULL;
		}
	}
	print_node(first_node);
}

char *infile_before(t_lst *lst)
{
	t_lst	*tmp;
	tmp = lst;
	while (tmp->prev != NULL)
	{
		if (tmp->token == PIPE)
			return(NULL);
		if (tmp->token == INFILE)
			return (tmp->cmd);
		tmp = tmp->prev;
	}
	return (NULL);
}

char	*infile_after(t_lst *lst)
{
	t_lst	*tmp;
	tmp = lst;
	char *infile;

	infile = NULL;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			return (infile);
		if (tmp->token == INFILE)
			infile = tmp->cmd;
		tmp = tmp->next;
	}
	return (infile);
}

char	*is_outfile_before(t_lst *lst)
{
	t_lst	*tmp;
	tmp = lst;
	while (tmp->prev != NULL)
	{
		if (tmp->token == PIPE)
			return(NULL);
		if (tmp->token == OUTFILE)
			return (tmp->cmd);
		tmp = tmp->prev;
	}
	return (NULL);
}

char	*is_outfile_after(t_lst *lst, t_node *node)
{
	t_lst	*tmp;
	t_lst *dup_tmp;
	char	*file;

	tmp = lst;
	file = NULL;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
		{
			///////////////////////CHECK SI INFILE APRES PIPE////////////////////////////////////
			dup_tmp = tmp;
			dup_tmp = dup_tmp->next;
			while(dup_tmp && dup_tmp->token != PIPE)
			{
				if (dup_tmp->token == INFILE)
					return(file);
				dup_tmp = dup_tmp->next;
			}
		}
		if (tmp->token == CMD)
			node->nb_cmd_in_block++;
		if(tmp->token == OUTFILE)
			file = tmp->cmd;
		if (tmp->token == PIPE && file)
			return (file);
		tmp = tmp->next;
	}
	return (file);
}

/*int	in_next_cmd(t_lst *lst)
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
}*/

/*char *out_next_cmd(t_lst *lst)
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
}*/

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
