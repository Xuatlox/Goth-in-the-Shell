/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:38:26 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/12 13:38:46 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_parsing(char c)
{
	write(2, "Minishell: syntax error near unexpected token `", 47);
	write(2, &c, 1);
	write(2, "'\n", 2);
}

void	error_heredoc(char *s, int code)
{
	if (code == 0)
	{
		write(2, "Minishell: warning: here-document delimited by end-of-file", 58);
		write(2, " (wanted `", 10);
		write(2, s, ft_strlen(s));
		write(2, "')\n", 3);
	}
	if (code == 1)
	{
		write(2, "Minishell: syntax error near unexpected token `newline'", 55);
	}
}
