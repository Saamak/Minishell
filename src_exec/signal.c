/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:19:39 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/25 18:26:21 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void sigint_handler() 
{
    printf("\n");
    rl_on_new_line();
   	rl_replace_line("", 0);
   	rl_redisplay();
	//exit_s = 130;
}

void sigquit_handler_in_exec()
{
	printf("Quit (core dumped)\n");
}

void sigint_handler_in_exec()
{
	printf("\n");
    rl_on_new_line();
   	rl_replace_line("", 0);
}

void signal_handle()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void signal_handle_exec()
{
	signal(SIGINT, sigint_handler_in_exec);
	signal(SIGQUIT, sigquit_handler_in_exec);
}