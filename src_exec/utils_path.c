/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:40:00 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/26 11:47:17 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

int	check(char *s, int start, int len)
{
	if (start > (int)ft_strlen(s))
		return (len = 0);
	if (len > (int)ft_strlen(s) - start)
		return (len = (int)ft_strlen(s) - start);
	return (len);
}

char	*cmd_find_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->my_envp[i])
	{
		if (ft_strncmp(data->my_envp[i], "PATH", 4) == 0)
		{
			return (data->my_envp[i]);
		}
		i++;
	}
	return (NULL);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data)
	{
		data->my_envp = NULL;
		data->commands_path = NULL;
		data->cmd = NULL;
	}
	data->cmd = NULL;
	return (data);
}
