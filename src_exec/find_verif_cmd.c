/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_verif_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:25:03 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/24 11:05:13 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

char	*cmd_get(t_data *data, t_command *ptr, int j)
{
	char	*tested_path;
	char	*cmd_slashed;
	
	cmd_slashed = ft_strjoin("/", ptr->cmd_args[j][0]);
	tested_path = test_cmd(data, ptr, cmd_slashed, j);
	free(cmd_slashed);
	return (tested_path);
}

char	*test_cmd(t_data *data, t_command *ptr, char *cmd_slashed, int j)
{
	char	*test;
	int		i;

	i = 0;
	while (data->commands_path[i])
	{
		test = ft_strjoin_two(data->commands_path[i], cmd_slashed);
		if (access(test, X_OK) == 0)
			return (test);
		else
			free(test);
		i++;
	}
	if (strcmp(ptr->cmd_args[j][0], "export") != 0 && strcmp(ptr->cmd_args[j][0], "echo") != 0 
		&& strcmp(ptr->cmd_args[j][0], "unset") != 0 && strcmp(ptr->cmd_args[j][0], "cd") != 0
		&& strcmp(ptr->cmd_args[j][0], "pwd") != 0 && strcmp(ptr->cmd_args[j][0], "env") != 0
		&& strcmp(ptr->cmd_args[j][0], "exit") != 0)
	{	
		printf("%s: Command not found\n", ptr->cmd_args[j][0]);
		data->exit_status = 127;
	}
	return (NULL);
}

char	*ft_strjoin_two(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		len_all;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len_all = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	result = malloc(sizeof(char) * len_all + 1);
	if (result == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
