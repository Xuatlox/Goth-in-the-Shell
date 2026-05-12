/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 06:00:49 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/10 14:05:20 by mcrenn           ###   ########.fr       */
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
	size_t			i;
	t_command		*current_cmd;
	t_quote_state	quote_ste;

	while (lexer)
	{
		if (lexer->cmd == NULL)
		{
			error_parsing('|');
			return (BAD_ARG);
		}
		current_cmd = lexer->cmd;
		while (current_cmd)
		{
			i = 0;
			quote_ste = NO_QTE;
			while (current_cmd->str && current_cmd->str[i])
				check_quotes(current_cmd->str[i++], &quote_ste);
			if (quote_ste == DOUBLE_QTE || quote_ste == SIMPLE_QTE)
				error_parsing(quote_ste);
			if (quote_ste != NO_QTE)
				return (BAD_ARG);
			current_cmd = current_cmd->next;
		}
		lexer = lexer->next;
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
t_token	*parsing(char *line, t_status *status, t_env *env)
{
	t_token		*lex;

	lex = lexer(line, status, env);
	if (*status == SUCCESS)
		*status = check_input(lex);
	if (!*status)
		expand(lex, env, status);
	if (!*status)
		remove_quotes(lex, status);
	else
		lst_clear_tkn(&lex);
	return (lex);
}
