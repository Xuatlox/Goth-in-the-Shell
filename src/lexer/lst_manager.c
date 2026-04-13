/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:38:30 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/13 04:58:47 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/func_dec.h"

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_token(t_token **lst, t_status *status)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = lst_newtoken(status);
	else
		ft_lstlast_token(*lst)->next = lst_newtoken(status);
}

t_command	*ft_lstlast_command(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_command	*lst_newcommand(char c, t_status *status)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
	{
		*status = ALLOCATION_FAILURE;
		return (NULL);
	}
	command->str = NULL;
	command->next = NULL;
	if (c)
		*status = charjoin(command, c);
	if (*status == ALLOCATION_FAILURE)
	{
		free(command);
		command = NULL;
	}
	return (command);
}

void	ft_lstadd_command(t_token *last_tkn, char c, t_status *status)
{
	if (!last_tkn)
		return ;
	if (!c)
	{
		if (!last_tkn->cmd || !ft_lstlast_command(last_tkn->cmd)->str)
			return ;
		ft_lstlast_command(last_tkn->cmd)->next = lst_newcommand(0, status);
	}
	else
	{
		if (!last_tkn->cmd)
			 last_tkn->cmd = lst_newcommand(c, status);
		else if (ft_lstlast_command(last_tkn->cmd)->str == NULL)
			*status = charjoin(ft_lstlast_command(last_tkn->cmd), c);
		else
			*status = charjoin(ft_lstlast_command(last_tkn->cmd), c);
	}
}

t_token		*lst_newtoken(t_status *status)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		*status = ALLOCATION_FAILURE;
		return (NULL);
	}
	token->infile = -1;
	token->outfile = -1;
	token->cmd = NULL;
	token->next = NULL;
	return (token);
}
