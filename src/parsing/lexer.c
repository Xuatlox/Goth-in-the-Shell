/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 03:28:47 by mcrenn            #+#    #+#             */
/*   Updated: 2026/07/15 11:20:23 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *cmd, t_status *state, t_minishell *shell)
{
	size_t			i;
	t_quote_state	quote_state;

	i = 0;
	quote_state = NO_QTE;
	shell->tkn_node = lst_newtoken(state);
	while (cmd && cmd[i] && *state == SUCCESS)
	{
		check_quotes(cmd[i], &quote_state);
		if (cmd[i] == '|' && quote_state == NO_QTE && *state == SUCCESS)
			ft_lstadd_token(&shell->tkn_node, state);
		else if (ft_isspace(cmd[i]) == 1
			&& quote_state == NO_QTE && *state == SUCCESS)
			ft_lstadd_command(ft_lstlast_token(shell->tkn_node), 0, state);
		else if ((cmd[i] == '<' || cmd[i] == '>') && quote_state == NO_QTE
			&& *state == SUCCESS)
			*state = redirect_manager(cmd,
					ft_lstlast_token(shell->tkn_node), &i, shell);
		else
			ft_lstadd_command(ft_lstlast_token(shell->tkn_node), cmd[i], state);
		if (cmd && cmd[i] && *state == SUCCESS)
			i++;
	}
	free(cmd);
	return (shell->tkn_node);
}
