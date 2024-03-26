/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:13:21 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/26 17:13:40 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void	triple_handle(t_lst **lst, t_command **node)
{
	int	i;
	int	j;

	i = 0;
	(*node)->cmd_args = malloc(sizeof (char**) * ((*node)->nb_cmd_in_block + 1));
	while (i < (*node)->nb_cmd_in_block)
	{
		j = 0;
		if ((*lst)->token == CMD)
		{
			(*node)->cmd_args[i] = malloc(sizeof (char*) * 2);
			(*node)->cmd_args[i][j] = strdup((*lst)->cmd);
			(*node)->cmd_args[i][j+1] = NULL;
			*lst = (*lst)->next;
			j++;
			while ((*lst) && (*lst)->token == ARGS)
			{
				char **temp = malloc(sizeof(char*) * (j + 2));
				memcpy(temp, (*node)->cmd_args[i], sizeof(char*) * (j + 1));
				free((*node)->cmd_args[i]);
				(*node)->cmd_args[i] = temp;
				(*node)->cmd_args[i][j] = strdup((*lst)->cmd);
				(*node)->cmd_args[i][j+1] = NULL;
				j++;
				*lst = (*lst)->next;
			}
			i++;
		}
		if (i != (*node)->nb_cmd_in_block)
			*lst = (*lst)->next;
	}
	(*node)->cmd_args[i] = NULL;
	while (((*lst) != NULL) && (*lst)->token != PIPE)
		*lst = (*lst)->next;
}

void	to_node(t_lst **lst, t_command **node, t_parse *parse)
{
	t_lst	*first;
	t_command	*first_node;
	int		i;

	i = 0;
	if (lst == NULL || node == NULL)
		return ;
	first = *lst;
	first_node = *node;
	(*node)->prev = NULL;
	(*node)->next = NULL;
	while ((*lst) != NULL)
	{
		if (cmd_exists_in_block(*lst) == 0)
		{
			check_outfile_create(*lst, parse);
			if ((*lst)->token == OUTFILE || (*lst)->token == CHEVRON_OUT)
			{
				(*node)->to_create = malloc (sizeof (char *) * parse->nb_out_to_create + 1);
				while (((*lst) != NULL) && (*lst)->token != PIPE && (*lst)->token != CMD)
				{
					if ((*lst)->token == OUTFILE)
					{
						if (i >= parse->nb_out_to_create)
							return ;
						(*node)->file_out = (*lst)->cmd;
						(*node)->to_create[i] = strdup((*lst)->cmd);
						i++;
					}
					(*node)->to_create[i] = NULL;
					(*lst) = (*lst)->next;
				}
				if (((*lst) != NULL) && (*lst)->token != CMD)
				{
					(*node)->next = malloc(sizeof(t_command));
					(*node)->next->prev = *node;
					(*node) = (*node)->next;
					(*node)->next = NULL;
				}
			}
		}
		if ((*lst) != NULL && (*lst)->token == CMD)
		{
			parse->i = 0;
			parse->nb_out_to_create = 0;
			check_outfile_create(*lst, parse);
			if (parse->nb_out_to_create > 0)
			{
				(*node)->to_create = malloc(sizeof (char*) * (parse->nb_out_to_create + 1));
				if ((*node)->to_create != NULL)
					(*node)->to_create[parse->nb_out_to_create] = NULL;
			}
			(*node)->file_in = infile_after(*lst);
			if (!(*node)->file_in)
				(*node)->file_in = infile_before(*lst);
			(*node)->file_out = is_outfile_after(*lst, *node, parse);
			if (!((*node)->file_out))
				(*node)->file_out = is_outfile_before(*lst, *node, parse);
			triple_handle(lst, node);
		}
		if ((*lst) != NULL && (*node)->nb_cmd_in_block != 0)
		{
			(*node)->next = malloc(sizeof(t_command));
			(*node)->next->prev = *node;
			(*node) = (*node)->next;
			(*node)->next = NULL;
		}
		if (*lst)
			(*lst) = (*lst)->next;
	}
}

void	check_outfile_create(t_lst *lst, t_parse *parse)
{
	t_lst	*tmp;
	int file;

	file = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE && file == 1)
			return ;
		if (tmp->token == OUTFILE)
			parse->nb_out_to_create++;
		tmp = tmp->next;
	}
}

char	*infile_before(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp->prev != NULL)
	{
		if (tmp->token == PIPE)
			return (NULL);
		if (tmp->token == INFILE)
			return (tmp->cmd);
		tmp = tmp->prev;
	}
	return (NULL);
}

char	*infile_after(t_lst *lst)
{
	t_lst	*tmp;
	char	*infile;

	tmp = lst;
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

char	*is_outfile_before(t_lst *lst, t_command *node, t_parse *parse)
{
	t_lst	*tmp;
	char	*first_out;
	int		bool;

	bool = 0;
	tmp = lst;
	first_out = NULL;
	while (tmp->prev != NULL)
	{
		if (tmp->token == PIPE)
			return (NULL);
		if (tmp->token == OUTFILE)
		{
			first_out = tmp->cmd;
			bool = 1;
			if (bool == 1)
				to_create(node, tmp->cmd, parse);
			if (tmp->prev->token == APPEND)
				node->append = 1;
		}
		tmp = tmp->prev;
	}
	return (first_out);
}

char	*is_outfile_after(t_lst *lst, t_command *node, t_parse *parse)
{
	t_lst	*tmp;
	t_lst	*dup_tmp;
	char	*file;

	(void)parse;
	tmp = lst;
	file = NULL;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
		{
			dup_tmp = tmp;
			dup_tmp = dup_tmp->next;
			while (dup_tmp && dup_tmp->token != PIPE)
			{
				if (dup_tmp->token == INFILE)
					return (file);
				dup_tmp = dup_tmp->next;
			}
		}
		if (tmp->token == CMD)
			node->nb_cmd_in_block++;
		if (tmp->token == OUTFILE)
		{
			if (tmp->prev->token == APPEND)
				node->append = 1;
			else
				node->append = 0;
			file = tmp->cmd;
			to_create(node, file, parse);
		}
		if (tmp->token == PIPE && file)
			return (file);
		tmp = tmp->next;
	}
	return (file);
}

void	to_create(t_command *node, char *outfile, t_parse *parse)
{
	if (parse->i <= parse->nb_out_to_create)
	{
		node->to_create[parse->i] = strdup(outfile);
		parse->i++;
	}
}

int	cmd_exists_in_block(t_lst *lst)
{
	t_lst	*tmp;
	int		cmd;

	cmd = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->token == CMD)
			cmd = 1;
		if (tmp->token == PIPE && cmd == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
