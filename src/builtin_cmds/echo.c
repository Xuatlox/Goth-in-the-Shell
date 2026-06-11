/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 10:57:59 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the '-n' specifier is present in the args list, and puts
 * the pointer where the first word that needs to be printed starts
 *
 * @param args Pointer to the list of arguments following 'cd'
 * (NULL if no arguments)
 * @return 0 if '-n' is specified in the args list, else 1
 */
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
			i = 1;
		}
		else
			break ;
	}
	return (res);
}

/**
 * @brief Mimics the behavior of the echo command in bash
 *
 * @param args List of arguments following 'cd' (NULL if no arguments)
 * @param fd_out Fd where the output must be sent
 * @return 0 on success, 1 if an error occurred
 */
int	exec_echo(t_command *args, const int fd_out)
{
	int		newline;
	size_t	size;

	newline = is_newline(&args);
	while (args)
	{
		size = ft_strlen(args->str);
		if (write(fd_out, args->str, size) < 0)
			return (1);
		if (args->next && args->str && *args->str)
			if (write(fd_out, " ", 1) < 0)
				return (1);
		args = args->next;
	}
	if (newline)
		if (write(fd_out, "\n", 1) < 0)
			return (1);
	return (0);
}
