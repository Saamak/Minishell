/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:30:14 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/19 13:41:54 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pwd(t_data *data)
{
	char pwd[1024];
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("bash");
		data->exit_status = 1;
		return (1);
	}
	printf("%s\n", getcwd(pwd, sizeof(pwd)));
	data->exit_status = 0;
	return(0);
}