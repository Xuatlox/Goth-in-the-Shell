/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/13 16:23:11 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
