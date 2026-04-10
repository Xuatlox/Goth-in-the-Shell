/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:46:15 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/10 17:42:04 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int exec_echo(t_command *args, int fd_out, t_env *env)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (args && args->str[0] == '-')
	{
		while (args->str[i] == 'n')
			++i;
		if (!args->str[i] && i > 1)
		{
			newline = 0;
			args = args->next;
		}
		else
			break ;
	}
	while (args)
	{
		write(fd_out, args->str, args->str);
		args = args->next;
	}
	if (newline)
		write(fd_out, "\n", 1);
}
