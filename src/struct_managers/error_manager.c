/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:38:26 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/12 16:46:48 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_parsing(char c)
{
	if (c)
	{
		write(2, "Minishell: syntax error near unexpected token `", 47);
		write(2, &c, 1);
		write(2, "'\n", 2);
	}
	else
		write(2, "Minishell: syntax error near unexpected token `newline'\n", 56);
}

void	error_heredoc(char *s)
{
	write(2, "Minishell: warning: here-document delimited by end-of-file", 58);
	write(2, " (wanted `", 10);
	write(2, s, ft_strlen(s));
	write(2, "')\n", 3);
}
