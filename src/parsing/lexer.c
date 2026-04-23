/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 03:28:47 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/23 22:39:02 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_manager(t_token **tkn_node, t_status *status)
{
	int	fd[2];
	if (pipe(fd) == -1)
	{
		*status = PIPE_FAILURE;
		return ;
	}
	if (ft_lstlast_token(*tkn_node)->outfile > 0)
		close(ft_lstlast_token(*tkn_node)->outfile);
	ft_lstlast_token(*tkn_node)->outfile = fd[1];
	ft_lstadd_token(tkn_node, status);
	if (*status != SUCCESS)
	{
		close(fd[0]);
		close(fd[1]);
		ft_lstlast_token(*tkn_node)->outfile = -1;
		return ;
	}
	if (ft_lstlast_token(*tkn_node)->infile > 0)
		close(ft_lstlast_token(*tkn_node)->infile);
	ft_lstlast_token(*tkn_node)->infile = fd[0];
}

/*
	Convert command line to node with command inside
	IF "<", ">", "<<", ">>" open the corresponded fd
	IF "|" New node
*/
t_token *lexer(char* cmd, t_status *status)
{
	size_t			i;
	t_token			*tkn_node;
	t_quote_state	quote_state;

	i = 0;
	quote_state = NO_QTE;
	tkn_node = lst_newtoken(status);
	while (cmd[i] && *status == SUCCESS)
	{
		//printf("|'%s'|'%d' '%c'|\n", cmd, cmd[i], cmd[i]);
		check_quotes(cmd[i], &quote_state);
		if (cmd[i] == '|' && quote_state == NO_QTE && *status == SUCCESS)
			pipe_manager(&tkn_node, status);
		else if (ft_isspace(cmd[i]) == 1
			&& quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_command(ft_lstlast_token(tkn_node), 0, status);
		else if ((cmd[i] == '<' || cmd[i] == '>') && quote_state == NO_QTE
			&& *status == SUCCESS)
			redirect_manager(cmd, tkn_node, status, &i);
		else
			ft_lstadd_command(ft_lstlast_token(tkn_node), cmd[i], status);
		i++;
	}
	return (tkn_node);
}
