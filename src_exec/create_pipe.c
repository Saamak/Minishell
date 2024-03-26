/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:35:38 by kprigent          #+#    #+#             */
/*   Updated: 2024/03/26 15:07:06 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void file_open_create(t_command *ptr)
{
	int fd;
	int i;

	i = 0;
	while ( ptr->to_create && ptr->to_create[i + 1] != NULL)
	{
		fd = open(ptr->to_create[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
		{
			printf("bash: %s:Permission denied\n", ptr->to_create[i]);
			exit(EXIT_FAILURE);
		}
		close(fd);
		i++;
	}
	return ;
}

int create_pipe(t_data *data, t_command *ptr, int i)
{
	int pipe_fd[2];
	int pid;
	int b;

	b = 0;
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (i < ptr->nb_cmd_in_block - 1) // tant qu on est pas a la derniere commande on renvoit dans le pipe
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		else if (ptr->file_out) // redirection sortie si changement
		{
			dup2(data->fd_out, STDOUT_FILENO);
			close(data->fd_out);
		}
		if (bultins(ptr, data, i) == 1)
			exit(0);
		else if (execve(data->cmd[i], ptr->cmd_args[i], data->my_envp) == -1)
			exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	return (0);	
}

int open_fd(t_command *ptr, t_data *data)
{
	if (ptr->file_in) // ouverture fd in
	{	
		data->fd_in = open(ptr->file_in, O_RDONLY);
		if (data->fd_in < 0)
		{
			perror("bash");
			data->exit_status = 1;
			return(1);
		}	
	}
	//ici mettre heredoc
	if (ptr->file_out != NULL) // ouverture fd out
	{
		if (ptr->append == 1)
		{
			data->fd_out = open(ptr->file_out, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (data->fd_out < 0)
			{
				perror("bash");
				data->exit_status = 1;
				return(1);
			}
		}
		else
		{	
			data->fd_out = open(ptr->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if(data->fd_out < 0)
			{
				perror("bash");
				data->exit_status = 1;
				return (1);
			}
		}
	}
	return (0);
}

int	execution(t_command *ptr, t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (ptr->cmd_args && (ptr->file_out == NULL) && (ptr->nb_cmd_in_block == 1) && (bultins(ptr, data, i) == 1))
		return (0);
	file_open_create(ptr);
	data->cmd = malloc(sizeof(char *) * (ptr->nb_cmd_in_block + 1));
	if (data->cmd == NULL)
		return (0);
	while (j < ptr->nb_cmd_in_block) // recuperation des chemins d'executions
	{	
		data->cmd[j] = cmd_get(data, ptr, j);
		j++;
	}
	data->cmd[j] = NULL;
	j = 0;
	if (open_fd(ptr, data) == 1)
		return (1);
	if (ptr->file_in) // redirection entree
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	signal_handle_exec();
	while(i < ptr->nb_cmd_in_block)
	{
		create_pipe(data, ptr, i);
		i++;
	}
	while (j < ptr->nb_cmd_in_block)
	{
		waitpid(-1, NULL, 0);
		j++;
	}
	//free(data->cmd);
	return(0);
}