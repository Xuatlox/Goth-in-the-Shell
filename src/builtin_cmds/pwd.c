/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 13:40:46 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Mimics the behavior of the pwd command in bash
 *
 * @param fd_out Fd where the output must be sent
 * @param env List of environmental variables
 * @return 0 on success, 1 if an error occurred
 */
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
