/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:30:58 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/26 17:13:55 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

int exit_s = 0;

int len_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void free_all(t_parse *parse, t_lst *lst, t_data *data)
{
	int i;

	free_tab(parse);
	free_list(lst);
	if (data)
	{
		if (data->my_envp)
			free(data->my_envp);
		if (data->cmd)
		{
			i = 0;
			while (data->cmd[i])
			{
				free(data->cmd[i]);
				i++;
			}
			free(data->cmd);
		}
		if (data->commands_path)
		{
			i = 0;
			while (data->commands_path[i])
			{
				free(data->commands_path[i]);
				i++;
			}
			free(data->commands_path);
		}
		free(data);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*input;
	char	*prompt;
	t_parse	*parse;
	t_lst	*lst;
	t_command	*node;
	int stdin_copy;
	int stdout_copy;

	node = NULL;
	parse = NULL;
	lst = NULL;
	prompt = YELLOW"Mini-shell> "RESET;
	///////////////////////////////////////////////////////////////////////////
	int i;

	t_data	*data;

	data = init_data();
	data->exit_status = 0;
	i = 0;
	data->my_envp = malloc(sizeof(char *) * (len_envp(envp) + 1));
	while (envp[i])
	{
		data->my_envp[i] = envp[i];
		i++;
	}
	data->my_envp[i] = NULL;
	/////////////////////////////////////////////////////////////////////////
	while (1)
	{
		signal_handle();
		stdin_copy = dup(STDIN_FILENO);
		stdout_copy = dup(STDOUT_FILENO);
		node = init_nodes(node);
		lst = init_lst(lst);
		parse = init_t_parse(parse);
		input = readline(prompt);
		if (input == NULL) //CTRL -D
		{
			free_all(parse, lst, data);
			free(node);
			ft_putstr_fd("exit\n", 1);
			break;
		}
		if (checks(input, parse) == 0)
		{
			count_blocks(input, parse);
			parse->args = ft_splitting(input, parse);
			first_put_lst(&lst, parse, &node);
			if (parse->check == 0)
				to_node(&lst, &node, parse);
			parse->nb_blocks = 0;
		}
		free_list(lst);
		if (parse->check == 0)
			start_exec(node, data);
		add_history(input);
		free_tab(parse);

		dup2(stdin_copy, STDIN_FILENO);
    	dup2(stdout_copy, STDOUT_FILENO);

    	close(stdin_copy);
    	close(stdout_copy);
	}
	return (0);
}
