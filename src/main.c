/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:30:58 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/20 20:10:34 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*input;
	char	*prompt;
	t_parse	*parse;
	t_lst	*lst;
	t_node	*node;

	node = NULL;
	parse = NULL;
	lst = NULL;
	lst = init_lst(lst);
	parse = init_t_parse(parse);
	node = init_nodes(node);
	prompt = YELLOW"ZiziShellv1>"RESET;
	while (1)
	{
		input = readline(prompt);
		if (checks(input, parse) == 0)
		{
			count_blocks(input, parse);
		//	printf("number of blocs : %d\n", parse->nb_blocks);
			parse->args = ft_splitting(input, parse);
			first_put_lst(&lst, parse);
			to_node(&lst, &node);
		//	printf("INFILE : %s\n", node->file_in);
			// print_node(node);
		}
		free_list(&lst);
		parse->nb_blocks = 0;
		add_history(input);
	}
	return (0);
}

