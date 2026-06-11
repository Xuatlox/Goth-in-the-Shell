/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:04:55 by mcrenn            #+#    #+#             */
/*   Updated: 2026/06/09 14:58:14 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirect	is_redirect(char *str, t_redirect redir_state)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		error_parsing(0);
		return (ERROR_REDIR);
	}
	while (str[i] && ft_isspace(str[i]) > 0)
		i++;
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
	{
		if (redir_state == INPUT && str[i] == '>')
			error_parsing(0);
		else
			error_parsing(str[i]);
		return (ERROR_REDIR);
	}
	return (redir_state);
}

t_redirect	check_redirect(char *str)
{
	int			i;
	t_redirect	redirect;

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
	if (redirect == INPUT || redirect == TRUNC)
		redirect = is_redirect(str + i + 1, redirect);
	else if (redirect == HEREDOC || redirect == APPEND)
		redirect = is_redirect(str + i + 2, redirect);
	return (redirect);
}
