/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:00:41 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/25 18:35:06 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

int	checks(char *input, t_parse *parse)
{
	if (no_input(input))
		return (1);
	if (check_open_quote(input, parse))
		return (1);
	if (check_pipe_origin(input))
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

void	check_pipe_start(t_lst **lst, t_parse *parse, t_command **node)
{
	t_lst	*current;

	current = *lst;
	while (current != NULL)
	{
		if ((current->token == PIPE && current->next == NULL)
			|| (current->token == PIPE && current->next->token == PIPE))
		{
			error_lexer(*lst, parse,get_token_char((*lst)->token), *node);
			parse->check = 1;
			return ;
		}
		current = current->next;
	}
}

void	check_chevron(t_lst **lst, t_parse *parse, t_command **node)
{
	t_lst	*current;

	current = *lst;
	while (current != NULL)
	{
		if (current->token == CHEVRON_IN || current->token == CHEVRON_OUT
			|| current->token == APPEND || current->token == HEREDOC)
		{
			if (current->next == NULL || current->next->token == PIPE)
			{
				error_lexer(*lst, parse, get_token_char((*lst)->token), *node);
				parse->check = 1;
				return ;
			}
		}
		current = current->next;
	}
}

int	check_pipe_origin(char *input)
{
	if (input[0] == '|' || input[ft_strlen(input) - 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}
