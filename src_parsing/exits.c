/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:10:32 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/25 18:43:50 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void	error_parsing(t_parse *parse)
{
	if (parse->args != NULL)
		free_tab(parse);
	printf("syntax Error \n");
}

void	error_lexer(t_lst *lst, t_parse *parse, char *tok, t_command *node)
{
	(void)lst;
	if (node)
	{
		free_node(&node);
		free(node);
	}
	if (parse->args != NULL)
		free_tab(parse);
	if (ft_strcmp(tok, "CMD") == 0)
		printf("syntax Error \n");
	else
		printf("miniShell: Syntax error near unexpected token `%s'\n", tok);
}
