/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 06:45:16 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/13 16:19:46 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/func_dec.h"

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


