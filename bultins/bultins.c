/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:44:54 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/25 14:18:01 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int bultins(t_command *ptr, t_data *data, int i)
{
	if (strcmp(ptr->cmd_args[i][0], "echo") == 0)
	{	
		echo(data, ptr->cmd_args[i]);
		return(1);
	}
	else if (strcmp(ptr->cmd_args[i][0], "cd") == 0)
	{	
		cd(data, ptr->cmd_args[i][1]);
		return(1);
	}
	else if (strcmp(ptr->cmd_args[i][0], "env") == 0)
	{	
		env(data);
		return(1);
	}
	else if (strcmp(ptr->cmd_args[i][0], "export") == 0)
	{	
		export(data, ptr->cmd_args[i]);
		return (1);
	}
	else if (strcmp(ptr->cmd_args[i][0], "pwd") == 0)
	{	
		pwd(data);
		return(1);
	}
	else if (strcmp(ptr->cmd_args[i][0], "unset") == 0)
	{	
		unset(data, ptr->cmd_args[i]);
		return(1);
	}
	return (0);
}