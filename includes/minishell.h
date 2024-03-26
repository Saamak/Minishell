/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:48:10 by kleden            #+#    #+#             */
/*   Updated: 2024/03/26 16:00:16 by kprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <memory.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>
# include <termios.h>

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

# define R   "\x1B[31m"
# define G   "\x1B[32m"
# define Y   "\x1B[33m"
# define RESET "\x1B[0m"

extern int exit_s;

typedef struct s_data
{
	char	**cmd;
	char	**commands_path;
	char	**my_envp;
	int		exit_status;
	int 	fd_in;
	int		fd_out;
	int		nb_pipe;
}	t_data;

typedef struct s_command
{
	int		nb_cmd_in_block;
	char	*file_in;
	char	*file_out;
	int 	append;
	char 	**to_create;
	char 	***cmd_args;
	char 	*heredoc_text;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef enum s_enum
{
	CMD,
	ARGS,
	PIPE,
	CHEVRON_IN,
	CHEVRON_OUT,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
}	t_enum;

typedef struct s_lst
{
	t_enum			token;
	char			*cmd;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef struct s_parse
{
	int		nb_blocks;
	char	**args;
	int		i;
	int		is_args;
	int		check;
	int		nb_out_to_create;
}	t_parse;

///////////////////////////EXECUTION//////////////////////////////////////////////

//BULTINS
int bultins(t_command *ptr, t_data *data, int i);
int cd(t_data *data, char *path);
int echo(t_data *data, char **tab);
int unset(t_data *data, char **tab);
int pwd(t_data *data);
int env(t_data *data);
int export(t_data *data, char **tab);

// EXECUTION
t_data	*init_data(void);
int start_exec(t_command *ptr, t_data *data);
char	*cmd_get(t_data *data, t_command *ptr, int i);
char	*cmd_find_path(t_data *data);
char	*ft_strjoin_two(char const *s1, char const *s2);
char	*test_cmd(t_data *data, t_command *ptr, char *cmd_slashed, int j);
int		execution(t_command *ptr, t_data *data);
void	signal_handle_exec();
void	signal_handle();

//////////////////////////PARSING//////////////////////////////////////////////

char		**ft_splitting(char *s, t_parse *parse);
char		*my_strncpy(char *dest, char *src, int n);

// UTILS
t_parse		*init_t_parse(t_parse *parse);
int			count_w(char *s);
int			ft_strcmp(const char *str1, const char *str2);
int			is_white_space(char c);
void		count_blocks(char *input, t_parse *parse);
int			is_separator(char c);
int			is_printable(char c);

// CHECKS
int			check_open_quote(char *input, t_parse *parse);
void		check_pipe_start(t_lst **lst, t_parse *parse, t_command **node);
int			check_pipe_origin(char *input);
void		check_chevron(t_lst **lst, t_parse *parse, t_command **node);
int			no_input(char *input);
int			checks(char *input, t_parse *parse);

// ERRORS HANDLING
void		error_parsing(t_parse *parse);
void		error_lexer(t_lst *lst, t_parse *parse,char *tok, t_command*node);

// MEMORY
void		free_tab(t_parse *parse);
void		free_list(t_lst *lst); /////////////////////////////////////////
void		free_node(t_command **head);

// CHAINED LISTS INIT
t_lst		*init_lst(t_lst *lst);
t_command		*init_nodes(t_command *node);
void		first_put_lst(t_lst **lst, t_parse *parse, t_command **node);

// TOKENISATION
void		process_first_token(t_lst **lst, t_parse *parse, int *i);
void		process_remaining_tokens(t_lst **lst, t_parse *parse, int *i);
int			find_token(t_lst *lst, char *str, t_parse *parse);

// SEND TO EXEC
void		to_node(t_lst **lst, t_command **node, t_parse *parse);
char		*infile_before(t_lst *lst);
char		*infile_after(t_lst *lst);
char		*is_outfile_before(t_lst *lst, t_command *node, t_parse *parse);
char		*is_outfile_after(t_lst *lst, t_command *node, t_parse *parse);
int			cmd_exists_in_block(t_lst *lst);
void		check_outfile_create(t_lst *lst, t_parse *parse);
void		to_create(t_command *node, char *outfile, t_parse *parse);

//DISPLAY
const char	*get_token_name(int token);
char		*get_token_char(int token); ///////////NEW//////////////////////
void		print_parse(t_parse *parse);
void		print_node(t_command *node);
void		print_list(t_lst *lst);
void		search_append(t_lst *lst, t_command *node);
#endif
