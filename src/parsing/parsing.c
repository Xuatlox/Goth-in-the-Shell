/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 06:00:49 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/26 16:42:40 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Function that check if all cmd in the lexer are correct.
 *
 * @param lexer The linked list which lexing.
 * @return t_status
 */
static t_status	check_input(t_token **lexer)
{
	size_t			i;
	t_token			**current_node;
	t_command		**current_cmd;
	t_quote_state	quote_ste;

	current_node = lexer;
	while (current_node && *current_node)
	{
		if ((*current_node)->cmd == NULL)
		{
			error_parsing('|');
			return (BAD_ARG);
		}
		if ((*current_node)->cmd->str == NULL && !(*current_node)->cmd->next)
		{
			free((*current_node)->cmd);
			(*current_node)->cmd = NULL;
		}
		current_cmd = &(*current_node)->cmd;
		while (current_cmd && *current_cmd)
		{
			if ((*current_cmd)->next && (*current_cmd)->next->str == NULL)
			{
				free((*current_cmd)->next);
				(*current_cmd)->next = NULL;
			}
			i = 0;
			quote_ste = NO_QTE;
			while ((*current_cmd)->str && (*current_cmd)->str[i])
				check_quotes((*current_cmd)->str[i++], &quote_ste);
			if (quote_ste == DOUBLE_QTE || quote_ste == SIMPLE_QTE)
				error_parsing(quote_ste);
			if (quote_ste != NO_QTE)
				return (BAD_ARG);
			current_cmd = &(*current_cmd)->next;
		}
		current_node = &(*current_node)->next;
	}
	return (SUCCESS);
}

/**
 * @brief Function that send the command to the lexer and check if all inputs
 * are correct.
 *
 * @param line The line command.
 * @param status The state of the line comand.
 * @return t_token*
 */
t_token	*parsing(char *line, t_status *status, t_minishell *minishell)
{
	minishell->tkn_node = lexer(line, status, minishell);
	if (*status == SUCCESS)
		*status = check_input(&(minishell->tkn_node));
	if (!*status)
		expand(minishell, status);
	if (!*status)
		remove_quotes(minishell->tkn_node, status);
	if (*status)
		lst_clear_tkn(&(minishell->tkn_node));
	return (minishell->tkn_node);
}
