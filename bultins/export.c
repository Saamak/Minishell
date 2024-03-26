/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:09:28 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/22 16:21:44 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

char **sort_env(t_data *data, int nb_var)
{
	char **sorted_env;
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	sorted_env = malloc(sizeof(char*) * (nb_var + 1));
	if (sorted_env == NULL)
		return(NULL);
	while (k < nb_var)
	{
		j = 0;
		while(data->my_envp[j])
		{
			if(i == data->my_envp[j][0])
			{
				sorted_env[k] = data->my_envp[j];
				k++;
			}
			j++;
		}
		i++;
	}
	sorted_env[i] = NULL;
	return(sorted_env);
}

int parse_equal(char **tab, int i)
{
	int j;
	
	j = 0;
	while (tab[i][j])
	{
		if(!((tab[i][j] >='a' && tab[i][j] <= 'z') || (tab[i][j] >= 'A' && tab[i][j] <= 'Z') 
			|| (tab[i][j] >= '0' && tab[i][j] <= '9') || tab[i][j] == '+' || tab[i][j] == '_') && tab[i][j] != '=')
		{
			printf("bash: export: `%s': not a valid identifier\n", tab[i]);
			return(3);
		}
		if (tab[i][j] == '=')
			return (1);
		if (tab[i][j] == '+')
		{
			j++;
			if (tab[i][j] == '=')
				return (2);
		}
		j++;
	}
	return (0);
}

int check_if_already(char **tab, char **envp, int i)
{
	int j;
	int a;

	j = 0;
	while(envp[j])
	{
		a = 0;
		while(envp[j][a] == tab[i][a])
		{
			a++;
			if (envp[j][a]== '=' && tab[i][a] == '=')
				return (j);
			if (envp[j][a]== '=' && tab[i][a] == '+' && tab[i][a + 1] == '=')
				return (j);
		}
		j++;
	}
	return (-1);
}

void add_with_equal(t_data *data, char **tab, int i)
{
	int len;
	int pos;
	int j;
	char **new_envp;
	
	pos = check_if_already(tab, data->my_envp, i);
	if (pos != -1)
		data->my_envp[pos] = tab[i];
	else
	{
		len = 0;
		while(data->my_envp[len])
			len++;
		new_envp = malloc(sizeof(char *) * (len + 2));
		if (new_envp == NULL)
			return ;
		j = 0;
		while (j < len)
		{
			new_envp[j] = data->my_envp[j];
			j++;
		}
		new_envp[len] = strdup(tab[i]);
		new_envp[len + 1] = NULL;
		data->my_envp = new_envp;
	}
	return ;
}

void add_with_plus(t_data *data, char **tab, int i)
{
	int pos;
	int len;
	char **splited;
	char **new_envp;
	
	pos = check_if_already(tab, data->my_envp, i);
	if (pos != -1)
	{
		splited = ft_split(tab[i], '=');
		data->my_envp[pos] = ft_strjoin(data->my_envp[pos], splited[1]);
	}
	else
	{
		len = 0;
		while(data->my_envp[len])
			len++;
		new_envp = malloc(sizeof(char *) * (len + 2));
		if (new_envp == NULL)
			return ;
		while (i < len)
		{
			new_envp[i] = data->my_envp[i];
			i++;
		}
		new_envp[len] = strdup(tab[i]);
		new_envp[len + 1] = NULL;
		data->my_envp = new_envp;
	}
	return ;
}

int	export_with_var(t_data *data, char **tab)
{
	int c;
	int i;
	
	i = 1;
	if (tab[0] && tab[1]) // export avec ajout de variables dans env
	{
		while (tab[i])
		{
			c = parse_equal(tab,i);
			if (c == 1)
				add_with_equal(data, tab, i);
			else if (c == 2)	
				add_with_plus(data, tab, i);
			else if (c == 3)
				return (1);
			i++;
		}
	}
	return (0);
}

int export(t_data *data, char **tab)
{
	char **sorted_env;
	int i;
	int nb_var;
	
	i = 0;
	if (tab[0] && !tab[1]) // export seul
	{
		while (data->my_envp[i])
			i++;
		nb_var = i;
		sorted_env = sort_env(data, nb_var);
		i = 0;
		while (sorted_env[i])
		{
			printf("declare -x ");
			printf("%s\n", sorted_env[i]);
			i++;
		}
		data->exit_status = 0;
		return(0);
	}
	else
		export_with_var(data, tab);
	data->exit_status = 0;
	return (0);
}