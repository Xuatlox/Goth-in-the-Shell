/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 10:48:05 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(const int fd_out, const t_env *env)
{
	size_t	size;

	while (env)
	{
		if (env->val)
		{
			size = ft_strlen(env->name);
			write(fd_out, env->name, size);
			write(fd_out, "=", 1);
			size = ft_strlen(env->val);
			write(fd_out, env->val, size);
			write(fd_out, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
