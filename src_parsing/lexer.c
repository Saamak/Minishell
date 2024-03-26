/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:50:11 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/25 18:05:59 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

int	find_token(t_lst *lst, char *str, t_parse *parse)
{
	if (lst == NULL || str == NULL || parse == NULL)
		return (-1);
	if (str[0] == '|')
		lst->token = PIPE;
	else if (str[0] == '>' && str[1] == '>')
		lst->token = APPEND;
	else if (str[0] == '<' && str[1] == '<')
		lst->token = HEREDOC;
	else if (str[0] == '<')
		lst->token = CHEVRON_IN;
	else if (str[0] == '>')
		lst->token = CHEVRON_OUT;
	else if (lst->prev != NULL && lst->prev->token == CHEVRON_IN)
		lst->token = INFILE;
	else if (lst->prev != NULL && (lst->prev->token == CHEVRON_OUT
			|| lst->prev->token == APPEND))
		lst->token = OUTFILE;
	else if (lst->prev != NULL && lst->prev->token == CMD)
		lst->token = ARGS;
	else if (lst->prev != NULL && lst->prev->token == ARGS)
		lst->token = ARGS;
	else
		lst->token = CMD;
	parse->is_args = 1;
	return (0);
}
