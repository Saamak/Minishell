/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:16:44 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/13 15:13:12 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

char**	ft_splitting(char *s, t_parse *parse)
{
	int		words;
	int		open;
	int		j;
	int		last;
	int		i;
	char	 **result;

	open = 0;
	words = parse->nb_blocks;
	result = malloc ((words + 2) * sizeof (char*));
	last = 0;
	j = 0;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			open = !open;
			i++;
			continue ;
		}
		if (!open && (s[i] == ' ' || s[i] == '|' || s[i] == '>'
				|| s[i] == '<' || s[i] == '\0'))
		{
			if (i - last > 0)
			{
				result[j] = malloc(i - last + 1);
				my_strncpy(result[j], &s[last], i - last);
				result[j][i - last] = '\0';
				j++;
			}
			if (s[i] != ' ' && s[i] != '\0')
			{
				result[j] = malloc(2);
				result[j][0] = s[i];
				result[j][1] = '\0';
				j++;
			}
			last = i + 1;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*my_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	is_alphanumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= 'a' && str[i] <= 'z'))
			return (1);
		i++;
	}
	return (0);
}
