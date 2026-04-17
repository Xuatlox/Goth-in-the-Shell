/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:38:30 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/17 14:58:13 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/func_dec.h"

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

void	ft_lstadd_redirect(t_token *last_tkn, char *cmd, t_redirect redirect,
			t_status *status)
{
	int	i;

	i = 0;
	if (!last_tkn->cmd)
			 last_tkn->cmd = lst_newcommand(0, status);
		else if (ft_lstlast_command(last_tkn->cmd)->str)
			ft_lstlast_command(last_tkn->cmd)->next = lst_newcommand(0, status);
	if (redirect == INPUT)
		*status = charjoin(ft_lstlast_command(last_tkn->cmd), cmd[i]);
	else if (redirect == HEREDOC)
	{
		*status = charjoin(ft_lstlast_command(last_tkn->cmd), cmd[i]);
		*status = charjoin(ft_lstlast_command(last_tkn->cmd), cmd[i + 1]);
	}
	else if (redirect == TRUNC)
		*status = charjoin(ft_lstlast_command(last_tkn->cmd), cmd[i]);
	else if (redirect == APPEND)
	{
		*status = charjoin(ft_lstlast_command(last_tkn->cmd), cmd[i]);
		*status = charjoin(ft_lstlast_command(last_tkn->cmd), cmd[i + 1]);
	}
	ft_lstlast_command(last_tkn->cmd)->next = lst_newcommand(0, status);
}
