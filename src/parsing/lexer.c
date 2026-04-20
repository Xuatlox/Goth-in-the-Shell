/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 03:28:47 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/20 17:41:31 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirect_manager(char *str, /*t_token *tkn_node, */t_status *status,
	size_t *i)
{
	t_redirect	redir_state;
	char		*new_word;

	// ft_lstadd_redirect(ft_lstlast_token(tkn_node), str, redir_state,
	// 	status);

	new_word = NULL;
	redir_state = check_redirect(&str[*i]);
	if (redir_state == HEREDOC || redir_state == APPEND)
		(*i)++;
	(*i)++;
	while (str[*i] && ft_isspace(str[*i]) == 1 && *status == SUCCESS)
		(*i)++;
	while (str[*i] && *status == SUCCESS && ft_isspace(str[*i]) == 0)
	{
		str_charjoin(&new_word, str[*i]);
		(*i)++;
	}
	printf("W:%s\n", new_word);
}

void	pipe_manager(t_token *tkn_node, t_status *status)
{
	int	fd[2];
	if (!pipe(fd))
	{
		*status = PIPE_FAILURE;
		return ;
	}
	if (ft_lstlast_token(tkn_node)->outfile > 0)
		close(ft_lstlast_token(tkn_node)->outfile);
	ft_lstlast_token(tkn_node)->outfile = fd[1];
	ft_lstadd_token(&tkn_node, status);
	if (*status != SUCCESS)
	{
		close(fd[0]);
		close(fd[1]);
		ft_lstlast_token(tkn_node)->outfile = -1;
		return ;
	}
	if (ft_lstlast_token(tkn_node)->infile > 0)
		close(ft_lstlast_token(tkn_node)->infile);
	ft_lstlast_token(tkn_node)->infile = fd[0];
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
		check_quotes(cmd[i], &quote_state);
		if (cmd[i] == '|' && quote_state == NO_QTE && *status == SUCCESS)
			pipe_manager(tkn_node, status);
		else if (ft_isspace(cmd[i]) == 1
			&& quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_command(ft_lstlast_token(tkn_node), 0, status);
		else if ((cmd[i] == '<' || cmd[i] == '>') && quote_state == NO_QTE
			&& *status == SUCCESS)
			redirect_manager(cmd, /*tkn_node,*/ status, &i);
		else
			ft_lstadd_command(ft_lstlast_token(tkn_node), cmd[i], status);
		i++;
	}
	return (tkn_node);
}
