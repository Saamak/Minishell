/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:37:12 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/24 16:56:26 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"


void free_comp_var(char **comp)
{
	int i;

	i = 0;
	while (comp[i])
	{
		free(comp[i]);
		i++;
	}
	free(comp);	
}

int is_it_var(char *var, char **envp, char **tab, int z) // attention free poses au feeling
{
	char **comp;
	int a;
	int j;
	
	j = 0;
	while (envp[j])
	{
		comp = ft_split(envp[j], '=');
		a = 0;
		while (comp[0][a] == var[a])
		{
			if (comp[0][a + 1] == '\0' && var[a + 1] == '\0')
			{
				printf("%s", comp[1]);
				free_comp_var(comp);
				return (1);
			}
			a++;
		}
		j++;
		if (envp[j] == NULL && tab[z - 1] == NULL && tab[z + 1] == NULL)
		{	
			printf("\n");
			free_comp_var(comp);
			return (0);
		}
		free_comp_var(comp);
	}
	return (0);
}

int parse_var(t_data *data, char **tab, int z, int i)
{
	int start_i;
	int a;
	char *var;
	
	if (i == 0 && tab[z][i] == '$'  && tab[z][i + 1] == '\0')
		printf("$");
	else
	{
		i++;
		start_i = i;
		while (tab[z][i] != ' ' && tab[z][i] != '$' && tab[z][i] != '\0')
			i++;
		a = 0;
		var = malloc(sizeof(char) *(i - start_i + 1));
		if (var == NULL)
			return (1);
		while (a < i)
		{
			var[a] = tab[z][start_i];
			a++;
			start_i++;
		}
		var[a] = '\0';
		return(is_it_var(var, data->my_envp, tab, z));
	}
	return (0);
}

void check_simple_quote(char *tab)
{
	int i;
	int j;
	int nb_quote;

	nb_quote = 0;
	j = 0;
	i = 0;
	while(tab[i])
	{
		if(tab[i] == 39 && nb_quote != 2)
		{	
			i++;
			nb_quote++;
		}
		else
		{
			tab[j] = tab[i];
			j++;
			i++;
		}
	}
	tab[j] = '\0';
}

void check_quote(char *tab)
{
	int i;
	int j;
	int nb_quote;

	nb_quote = 0;
	j = 0;
	i = 0;
	while(tab[i])
	{
		if(tab[i] == 34 && nb_quote != 2)
		{
			i++;
			nb_quote++;
		}
		else
		{
			tab[j] = tab[i];
			j++;
			i++;
		}
	}
	tab[j] = '\0';
}

int parse(t_data *data, char **tab, int z)
{
	int i;
	
	i = 0;
	check_quote(tab[z]);
	while (i < (int)ft_strlen(tab[z]))
	{
		int len = ft_strlen(tab[z]);
		if (tab[z][i] == '$' && tab[z][i + 1] != '?' && tab[z][0] != 39 && tab[z][len] != 39)
		{
			parse_var(data, tab, z, i);
			return (0);
		}
		if (tab[z][i] == '$' && tab[z][i + 1] == '?')
		{
			printf("%d", data->exit_status);
			i++;
		}
		else
		{
			if (i == 0)
				check_simple_quote(tab[z]);
			printf("%c", tab[z][i]);
		}
		i++;
	}
	return (0);
}

int echo(t_data *data, char **tab)
{
	int z;

	if (tab[0] && !tab[1])
	{
		printf("\n");
		return (0);
	}
	z = 1;
	if(tab[0] && (tab[1][0] == '-' && tab[1][1] == 'n'))
		z++;
	while (tab[z])
	{
		parse(data, tab, z);
		printf(" ");
		z++;
	}
	if(tab[0] && tab[1][0] == '-' && tab[1][1] == 'n' && tab[1][2] == '\0')
		printf("");
	else
		printf("\n");
	data->exit_status = 0;
	return (0);
}