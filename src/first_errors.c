/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:00:41 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/13 15:09:23 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checks(char *input, t_parse *parse)
{
	if (no_input(input))
		return (1);
	if (check_open_quote(input, parse))
		return (1);
	return (0);
}

int	no_input(char *input)
{
	int	i;

	i = 0;
	while (is_white_space(input[i]))
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

int	check_open_quote(char *input, t_parse *parse)
{
	char	*cursor;
	int		d;
	int		s;

	cursor = input;
	d = 0;
	s = 0;
	while (*cursor)
	{
		if (*cursor == '"' || *cursor == '\'')
		{
			if (*cursor == '"')
				d++;
			if (*cursor == '\'')
				s++;
		}
		cursor++;
	}
	if (d % 2 != 0 || s % 2 != 0)
	{
		error_parsing(parse);
		return (1);
	}
	return (0);
}

void	check_pipe_start(t_lst **lst, t_parse *parse)
{
	t_lst	*current;

	current = *lst;
	if ((*lst)->token == PIPE)
	{
		error_lexer(*lst, parse);
		return ;
	}
	while (current && current->next != NULL)
		current = current->next;
	if (current && current->token == PIPE)
	{
		error_lexer(*lst, parse);
		return ;
	}
}

void	check_chevron_start(t_lst **lst, t_parse *parse)
{
	t_lst	*current;

	current = *lst;
	if ((*lst)->token == INFILE || (*lst)->token == OUTFILE)
	{
		error_lexer(*lst, parse);
		return ;
	}
	while (current && current->next != NULL)
		current = current->next;
	if (current && (current->token == INFILE || current->token == OUTFILE))
	{
		error_lexer(*lst, parse);
		return ;
	}
}
