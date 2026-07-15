/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 10:37:33 by mcrenn            #+#    #+#             */
/*   Updated: 2026/07/14 11:41:30 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear_current_nde(t_command **cmd)
{
	t_command *cmd_next;

	if (!(*cmd)->next)
	{
		if ((*cmd)->str)
			free((*cmd)->str);
		free(*cmd);
		*cmd = NULL;
		return (1);
	}
	if ((*cmd)->str)
		free((*cmd)->str);
	(*cmd)->str = (*cmd)->next->str;
	cmd_next = (*cmd)->next->next;
	free((*cmd)->next);
	(*cmd)->next = cmd_next;
	return (0);
}

void	remove_empty_node(t_minishell *minishell)
{
	t_token		*token;
	t_command	*cmd;
	t_command	*prev;

	token = minishell->tkn_node;
	while (token)
	{
		prev = NULL;
		cmd = token->cmd;
		while(cmd)
		{
			if (ft_strlen(cmd->str) == 0)
			{
				if (clear_current_nde(&cmd) == 1)
				{
					if (prev)
						prev->next = NULL;
					else
						token->cmd = NULL;
					break ;
				}
			}
			prev = cmd;
			cmd = cmd->next;
		}
		token = token->next;
	}
}
