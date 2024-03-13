/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:39:51 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/13 14:59:20 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_blocks(char *input, t_parse *parse)
{
	int open;
	int i;
	int is_word;

	i = 0;
	open = 0;
	is_word = 0;
	while (input[i])
	{
		while (input[i] == ' ')
		{
			i++;
			is_word = 0;
		}
		if (input[i] == '|' && input[i + 1] != '|' && input[i + 1] != '\0')
		{
			if (open == 0)
				parse->nb_blocks++;
			i++;
		}
		else if (input[i] == '\'' && input[i + 1] != '\'')
		{
			if (open == 1)
				open = 0;
			else if(open == 0)
			{
				open = 1;
				parse->nb_blocks++;
			}
		}
		else if (input[i] == '\"' && input[i + 1] != '\"')
		{
			if (open == 1)
				open = 0;
			else if (open == 0)
			{
				open = 1;
				parse->nb_blocks++;
			}
		}
		else if (input[i] == '<' && input[i + 1] != '<')
		{
			if (open == 0)
				parse->nb_blocks++;
		}
		else if (input[i] == '>' && input[i + 1] != '>')
		{
			if (open == 0)
				parse->nb_blocks++;
		}
		else if (open == 0 && is_printable(input[i])
			&& !is_word && !is_separator(input[i]))
		{
			parse->nb_blocks++;
			is_word = 1;
		}
		i++;
	}
}

int	is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_printable(char c)
{
	if (c > 32 && c <= 126)
		return (1);
	return (0);
}

