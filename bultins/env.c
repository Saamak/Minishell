/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:19:28 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/22 15:41:51 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int env(t_data *data)
{
	int i;

	i = 0;
	while (data->my_envp[i])
	{
		//if (strcmp(data-))
		printf("%s\n", data->my_envp[i]);
		i++;
	}
	data->exit_status = 0;
	return (0);
}