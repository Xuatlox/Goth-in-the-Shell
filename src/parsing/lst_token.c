/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:57:02 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/22 17:25:37 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
