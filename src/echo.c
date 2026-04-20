/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/20 11:17:11 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static int	is_newline(t_command **args)
{
	int	res;
	int	i;

	res = 1;
	i = 1;
	while (*args && (*args)->str[0] == '-')
	{
		while ((*args)->str[i] == 'n')
			++i;
		if (!(*args)->str[i] && i > 1)
		{
			res = 0;
			*args = (*args)->next;
		}
		else
			break ;
	}
	return (res);
}

int exec_echo(t_command *args, const int fd_out)
{
	int	newline;
	int	size;

	newline = is_newline(&args);
	while (args)
	{
		size = ft_strlen(args->str);
		write(fd_out, args->str, size);
		args = args->next;
	}
	if (newline)
		write(fd_out, "\n", 1);
	return (1);
}
