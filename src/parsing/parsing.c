/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 06:00:49 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/05 15:11:02 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Function that check if all cmd in the lexer are correct.
 *
 * @param lexer The linked list which lexing.
 * @return t_status
 */
static t_status	check_input(t_token *lexer)
{
	size_t	i;
	t_quote_state	quote_ste;

	if (lexer->cmd == NULL)
	{
		error_parsing('|');
		return (BAD_ARG);
	}
	while (lexer->cmd)
	{
		i = 0;
		quote_ste = NO_QTE;
		while (lexer->cmd->str && lexer->cmd->str[i])
			check_quotes(lexer->cmd->str[i++], &quote_ste);
		if (quote_ste == DOUBLE_QTE)
			error_parsing('\"');
		else if (quote_ste == SIMPLE_QTE)
			error_parsing('\'');
		if (quote_ste != NO_QTE)
			return (BAD_ARG);
		lexer->cmd = lexer->cmd->next;
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
t_token	*parsing(char *line, t_status *status/*, char **envp*/)
{
	t_token		*lex;
	t_token		*head_tkn;

	lex = lexer(line, status);
	head_tkn = lex;
	while (lex && *status == SUCCESS)
	{
		*status = check_input(lex);
		lex = lex->next;
	}

	if (*status != SUCCESS)
		lst_clear_tkn(&head_tkn);
	return (head_tkn);
}
