/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:24:47 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/19 11:23:35 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int compare(char **envp, char **tab, int i, int j)
{
	int a;
	
	a = 0;
	while (envp[i][a] == tab[j][a])
	{
		a++;
		if (tab[j][a] == '\0' && envp[i][a] == '=')
			return (1);
	}
	return (0);
}

void delete(char **envp, int i)
{
	envp[i] = envp[i + 1];
	i++;
	while (envp[i + 1])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	return ;
}

int unset(t_data *data, char **tab)
{
	int i;
	int j;

	j = 0;
	while (tab[j])
	{
		i = 0;
		while (data->my_envp[i])
		{
			if (compare(data->my_envp, tab, i, j) == 1)
			{
				delete(data->my_envp, i);
			}
			i++;
		}
		j++;
	}
	data->exit_status = 0;
	return (0);
}