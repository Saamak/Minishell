#include "minishell.h"

int	find_token(t_lst *lst, char *str, t_parse *parse)
{
	if (lst == NULL || str == NULL || parse == NULL)
		return (-1);
	if (str[0] == '|')
		lst->token = PIPE;
	else if (lst->prev != NULL && lst->prev->token == CHEVRON_IN)
		lst->token = INFILE;
	else if (lst->prev != NULL && lst->prev->token == CHEVRON_OUT)
		lst->token = OUTFILE;
	else if (lst->prev != NULL && lst->prev->token == CMD)
		lst->token = ARGS;
	else if (lst->prev != NULL && lst->prev->token == ARGS)
		lst->token = ARGS;
	else if (str[0] == '<')
		lst->token = CHEVRON_IN;
	else if (str[0] == '>')
		lst->token = CHEVRON_OUT;
	else
		lst->token = CMD;
	parse->is_args = 1;
	return (0);
}
