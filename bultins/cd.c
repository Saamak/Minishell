/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:48 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/19 13:29:07 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

int error_msg(char *first, char* second)
{
	perror(ft_strjoin(first, second));
	return(1);
}

int cd(t_data *data, char *path)
{
//	char *path= "test";
	
	if (chdir(path) == -1)
	{
		data->exit_status = 1;
		error_msg("bash: cd:", path);
	}
	data->exit_status = 0;
	return(0);
}