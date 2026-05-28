/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:38:26 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/28 16:33:54 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_parsing(char c)
{
	write(2, "goth_in_the_shell: ", 19);
	if (c)
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &c, 1);
		write(2, "'\n", 2);
	}
	else
		write(2, "syntax error near unexpected token `newline'\n", 45);
}

void	error_heredoc(char *s)
{
	write(2, "goth_in_the_shell: ", 19);
	write(2, "warning: here-document delimited by end-of-file", 47);
	write(2, " (wanted `", 10);
	write(2, s, ft_strlen(s));
	write(2, "')\n", 3);
}
