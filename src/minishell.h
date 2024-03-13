/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:04:21 by ppitzini          #+#    #+#             */
/*   Updated: 2024/03/13 15:06:04 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

# define R   "\x1B[31m"
# define G   "\x1B[32m"
# define Y   "\x1B[33m"
# define RESET "\x1B[0m"

typedef struct s_node
{
	int		nb_cmd_in_block;
	char	*file_in;
	char	*file_out;
}	t_node;

typedef enum s_enum
{
	CMD,
	ARGS,
	PIPE,
	CHEVRON_IN,
	CHEVRON_OUT,
	INFILE,
	OUTFILE,
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
}	t_parse;

# define RESET   "\x1B[0m"
# define RED     "\x1B[31m"
# define GREEN   "\x1B[32m"
# define YELLOW  "\x1B[33m"
# define BLUE    "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN    "\x1B[36m"
# define WHITE   "\x1B[37m"

int			main(void);
char		**ft_splitting(char *s, t_parse *parse);
char		*my_strncpy(char *dest, char *src, int n);

// UTILS
t_parse		*init_t_parse(t_parse *parse);
void		print_parse(t_parse *parse);
void		print_list2(t_node *node);
void		free_tab(t_parse *parse);
void		free_list(t_lst **head);
int			count_w(char *s);
int			ft_strcmp(const char *str1, const char *str2);
int			is_alpha(char c);
int			is_alphanumeric(char *str);

// CHECKS
int			check_open_quote(char *input, t_parse *parse);
void		check_pipe_start(t_lst **lst, t_parse *parse);
int			no_input(char *input);
void		error_parsing(t_parse *parse);
int			is_white_space(char c);
void		count_blocks(char *input, t_parse *parse);
int			separator_after(char *input, int i, t_parse *parse);
int			is_separator(char c);
int			is_printable(char c);
int			next_is_end(char *input, int i);
int			checks(char *input, t_parse *parse);

t_lst		*init_lst(t_lst *lst);
t_node		*init_nodes(t_node *node);
void		process_first_token(t_lst **lst, t_parse *parse, int *i);
void		process_remaining_tokens(t_lst **lst, t_parse *parse, int *i);
void		first_put_lst(t_lst **lst, t_parse *parse);
void		print_list(t_lst *lst);

t_node		*init_commands(t_node *node);
int			find_token(t_lst *lst, char *str, t_parse *parse);
void		error_lexer(t_lst *lst, t_parse *parse);
const char	*get_token_name(int token);
void		to_node(t_lst **lst, t_node **node);

#endif
