/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:10:32 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/13 15:00:35 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_parsing(t_parse *parse)
{
	if (parse->args != NULL)
		free_tab(parse);
	printf("Syntax Error\n");
}

void	error_lexer(t_lst *lst, t_parse *parse)
{
	if (lst)
		free_list(&lst);
	if (parse->args != NULL)
		free_tab(parse);
	printf("Syntax Error\n");
}
