/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 03:28:47 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/26 16:40:47 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*lexer(char* cmd, t_status *status, t_minishell *shell)
{
	size_t			i;
	t_token			*tkn_node;
	t_quote_state	quote_state;

	i = 0;
	quote_state = NO_QTE;
	tkn_node = lst_newtoken(status);
	while (cmd && cmd[i] && *status == SUCCESS)
	{
		check_quotes(cmd[i], &quote_state);
		if (cmd[i] == '|' && quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_token(&tkn_node, status);
		else if (ft_isspace(cmd[i]) == 1
			&& quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_command(ft_lstlast_token(tkn_node), 0, status);
		else if ((cmd[i] == '<' || cmd[i] == '>') && quote_state == NO_QTE
			&& *status == SUCCESS)
			*status = redirect_manager(cmd, ft_lstlast_token(tkn_node), &i, shell);
		else
			ft_lstadd_command(ft_lstlast_token(tkn_node), cmd[i], status);
		if (cmd && cmd[i] && *status == SUCCESS)
			i++;
	}
	free (cmd);
	return (tkn_node);
}
