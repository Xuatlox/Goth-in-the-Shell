/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuatlox <xuatlox@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:01:05 by xuatlox           #+#    #+#             */
/*   Updated: 2026/04/29 17:43:56 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exec_pwd(const int fd_out, t_env *env)
{
	char	*path;
	int		size;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = *get_env(env, "PWD");
		if (!path)
			return (0);
	}
	size = ft_strlen(path);
	write(fd_out, path, size);
	write(fd_out, "\n", 1);
	free(path);
	return (1);
}
