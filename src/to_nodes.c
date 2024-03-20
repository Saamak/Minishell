/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:13:21 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/20 08:04:38 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_node(t_lst **lst, t_node **node)
{
	t_lst    *first;
	t_node    *first_node;
	t_outfile_info *info;
	int        i;

	i = 0;
	if (lst == NULL || node == NULL)
		return;
	first = *lst;
	(*node) = malloc(sizeof(t_node));
	first_node = (*node);
	(*node)->prev = NULL;
	(*node)->next = NULL;

	while ((*lst) != NULL)
	{
		printf("Token : %s\n", get_token_name((*lst)->token));
		if((*lst)->token == CMD)
		{
			info = malloc(sizeof(t_outfile_info));
			cmd_process(*lst, *node, info);
			if(info->lst != NULL)
    			*lst = info->lst;
			printf("lst->cmd : %s\n", (*lst)->cmd);
			free(info);
			printf("lst-next->cmd : %s\n", (*lst)->next->cmd);
			if(next_cmd_exists((*lst)->next))
			{
				(*node)->next = malloc(sizeof(t_node));
				(*node)->next->prev = *node;
				(*node) = (*node)->next;
				(*node)->next = NULL;
			}
		}
		*lst = (*lst)->next;
	}
	*lst = first;
	(*node) = first_node;
}

void	cmd_process(t_lst *lst, t_node *node, t_outfile_info *info)
{
	node->file_in = infile_after(lst);
	if (!node->file_in)
		node->file_in = infile_before(lst);

	node->file_out = is_outfile_after(lst, node, info);
	if(!(node->file_out))
		node->file_out = is_outfile_before(lst);
	return ;
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
		{
			printf(G"Found INFILE Before CMD  : %s\n"RESET, tmp->cmd);  // Print the command associated with the INFILE token
			return (tmp->cmd);
		}
		tmp = tmp->prev;
	}
	printf(R"No INFILE before CMD \n"RESET);
	return (NULL);
}

char	*infile_after(t_lst *lst)
{
	t_lst	*tmp;
	char 	*infile;

	tmp = lst;
	infile = NULL;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			return (infile);
		if (tmp->token == INFILE)
		{
			printf(G"Found INFILE After CMD  : %s\n"RESET, tmp->cmd);
			infile = tmp->cmd;
		}
		tmp = tmp->next;
	}
	printf(R"No INFILE after CMD \n"RESET);
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
		{
			printf(G"Found OUTFILE token Before CMD  : %s\n"RESET, tmp->cmd);
			return (tmp->cmd);
		}
		tmp = tmp->prev;
	}
	printf(R"No OUTFILE before CMD \n"RESET);
	return (NULL);
}

char	*is_outfile_after(t_lst *lst, t_node *node, t_outfile_info *info)
{
	t_lst	*tmp;
	tmp =	lst;
	char	*file;
	int pipe;
	int j;
	int i;

	i = 0;
	pipe = 0;
	file = NULL;
	while (tmp != NULL)
	{
		if (tmp->token == CMD)
		{
			j = 0;
			node->nb_cmd_in_block++;
			node->cmd_args = malloc(sizeof(char **) * 100);
			node->cmd_args[i] = malloc(sizeof(char *) * 100);
			node->cmd_args[i][j] = malloc(sizeof(char *) * 100);
			node->cmd_args[i][j] = strdup(tmp->cmd);
			printf("COMMAND STORED : %s \n", node->cmd_args[i][j]);
			while (tmp->token == ARGS)
			{

				j++;
				node->cmd_args[i][j] = tmp->cmd;
				tmp = tmp->next;
			}
			i++;
		}
		if (tmp->token == PIPE)
			pipe++;
		if(tmp->token == OUTFILE)
		{
			printf(G"Found OUTFILE token After CMD  : %s\n"RESET, tmp->cmd);
			file = tmp->cmd;
		}
		if (tmp->token == INFILE && pipe == 1)
		{
			info->lst = tmp;
			return (file);
		}
		if (tmp->token == PIPE && file)
		{
			printf("DD");
			info->lst = tmp;
			return (file);
		}
		tmp = tmp->next;
	}
	printf("DD");
	printf("lst->cmd AFTER : %s\n", tmp->token);
	info->lst = tmp;
	return (file);
}

int	next_cmd_exists(t_lst *lst)
{
	t_lst	*tmp;
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token == CMD)
		{
			printf(Y"\nNext CMD Exists\n"RESET);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// int	in_next_cmd(t_lst *lst)
// {
// 	printf(Y"\nINChecking Next Command\n"RESET);
// 	t_lst	*tmp;
// 	tmp = lst;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->token == CMD)
//  		{
// 				if (ft_strcmp(infile_before(tmp), "STDIN") != 0 || ft_strcmp(infile_after(tmp), "STDIN") != 0)
// 					return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// char *out_next_cmd(t_lst *lst)
// {
// 	printf(Y"\nOUTChecking Next Command\n"RESET);
// 	t_lst	*tmp;
// 	tmp = lst;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->token == CMD)
//  		{
// 				if (ft_strcmp(is_outfile_before(tmp), "STDOUT") != 0)
// 					return (is_outfile_before(tmp));
// 				if (ft_strcmp(is_outfile_after(tmp), "STDOUT") != 0)
// 					return (is_outfile_after(tmp));
// 		}
// 		tmp = tmp->next;
// 	}
// 	return ("STDOUT");
// }

