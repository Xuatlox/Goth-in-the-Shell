/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 10:48:05 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(const int fd_out, t_env *env)
{
	char	*path;
	size_t	size;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = *get_env(env, "PWD");
		if (!path)
			return (1);
	}
	size = ft_strlen(path);
	write(fd_out, path, size);
	write(fd_out, "\n", 1);
	free(path);
	return (0);
}
