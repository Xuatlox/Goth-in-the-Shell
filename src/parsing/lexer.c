/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 03:28:47 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/16 13:28:59 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Allocate a new space for the gived string, size of len.
*/
t_status	charjoin(t_command *src, char c)
{
	char	*tmp;
	size_t		size;

	if (!c || !src)
		return (SUCCESS);
	if (!src->str)
		size = 2;
	else
		size = ft_strlen(src->str) + 2;
	tmp = ft_calloc(size, 1);
	if (!tmp)
		return (ALLOCATION_FAILURE);
	if (src->str)
		ft_strlcat(tmp, src->str, size - 1);
	ft_strlcat(tmp, &c, size);
	if (src->str)
		free(src->str);
	src->str = tmp;
	return (SUCCESS);
}

/*
	Convert command line to node with command inside
	IF "<", ">", "<<", ">>" open the corresponded fd
	IF "|" New node
*/
t_token *lexer(char* cmd, t_status *status)
{
	int				i;
	t_token			*tkn_node;
	t_quote_state	quote_state;
	t_redirect		redir_state;

	i = 0;
	quote_state = NO_QTE;
	tkn_node = lst_newtoken(status);
	while (cmd[i] && *status == SUCCESS)
	{
		redir_state = check_redirect(cmd + i);
		check_quotes(cmd[i], &quote_state);
		if (cmd[i] == '|' && quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_token(&tkn_node, status);
		else if (ft_isspace(cmd[i]) == 1
			&& quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_command(ft_lstlast_token(tkn_node), 0, status);
		else if (redir_state != NONE && quote_state == NO_QTE
			&& *status == SUCCESS)
		{
			ft_lstadd_redirect(ft_lstlast_token(tkn_node), cmd + i, redir_state,
				status);
			if (redir_state == HEREDOC || redir_state == APPEND)
				i++;
		}
		else
			ft_lstadd_command(ft_lstlast_token(tkn_node), cmd[i], status);
		i++;
	}
	return (tkn_node);
}
