/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 03:28:47 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/13 04:44:49 by mcrenn           ###   ########.fr       */
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

t_redirect	check_redirect(char *str)
{
	int	i;
	t_redirect redirect;

	i = 0;
	if (str[i + 1] && str[i] == '<' && str[i + 1] == '<')
		redirect = HEREDOC;
	else if (str[i + 1] && str[i] == '>' && str[i + 1] == '>')
		redirect = APPEND;
	else if (str[i] == '<')
		redirect = INPUT;
	else if (str[i] == '>')
		redirect = TRUNC;
	else
		redirect = NONE;
	return (redirect);
}

void	check_quotes(char c, t_quote_state *quote_state)
{
	if (c == '\'')
	{
		if (*quote_state == NO_QTE)
			*quote_state = SIMPLE_QTE;
		else if (*quote_state == SIMPLE_QTE)
			*quote_state = NO_QTE;
	}
	else if (c == '\"')
	{
		if (*quote_state == NO_QTE)
			*quote_state = DOUBLE_QTE;
		else if (*quote_state == DOUBLE_QTE)
			*quote_state = NO_QTE;
	}
}

/*
	Convert command line to node with command inside
	IF "<", ">", "<<", ">>" open the corresponded fd
	IF "|" New node
*/
t_token *lexer(const char* cmd, t_status *status)
{
	int				i;
	t_token			*tkn_node;
	t_quote_state	quote_state;

	i = 0;
	quote_state = NO_QTE;
	tkn_node = lst_newtoken(status);
	while (cmd[i] && *status == SUCCESS)
	{
		check_quotes(cmd[i], &quote_state);
		if (cmd[i] == '|' && quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_token(&tkn_node, status);
		else if (ft_isspace(cmd[i]) == 1
			&& quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_command(ft_lstlast_token(tkn_node), 0, status);
		else
			ft_lstadd_command(ft_lstlast_token(tkn_node), cmd[i], status);
		i++;
	}
	return (tkn_node);
}
