/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:50:47 by kleden            #+#    #+#             */
/*   Updated: 2024/03/26 12:00:57 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void free_ptr(t_command *ptr)
{
	t_command *tmp;
	int i;
	int j;

	i = 0;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		if(tmp->file_out)
			free(tmp->file_out);
		if(tmp->file_in)
			free(tmp->file_in);
		if(tmp->to_create)
		{
			while (tmp->to_create[i])
			{
				free(tmp->to_create[i]);
				i++;
			}
			free(tmp->to_create);
		}
		if (tmp->cmd_args)
		{
			i = 0;
			while (tmp->cmd_args[i])
			{
				j = 0;
				while(tmp->cmd_args[i][j])
				{
					free(tmp->cmd_args[i][j]);
					j++;
				}
				free(tmp->cmd_args[i]);
				i++;
			}
			free(tmp->cmd_args);
		}
		if (tmp->heredoc_text)
			free(tmp->heredoc_text);
		free(tmp);
	}
	free(ptr);
}

int start_exec(t_command *ptr, t_data *data)
{
	t_command *ptr_mem;
	
	ptr_mem = ptr;
	data->commands_path = ft_split(cmd_find_path(data), ':');
	while (ptr)
	{
		execution(ptr, data);
		ptr = ptr->next;
	}
	free_ptr(ptr_mem);
	return (0);
}