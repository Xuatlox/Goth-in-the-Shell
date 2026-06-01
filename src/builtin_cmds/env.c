/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 11:06:20 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Mimics the behavior of the env command in bash
 *
 * @param fd_out Fd where the output must be sent
 * @param env List of environmental variables
 * @return 0 on success, 1 if an error occurred
 */
int	exec_env(const int fd_out, const t_env *env)
{
	size_t	size;

	while (env)
	{
		if (env->val)
		{
			size = ft_strlen(env->name);
			if (write(fd_out, env->name, size) < 0)
				return (1);
			if (write(fd_out, "=", 1) < 0)
				return (1);
			size = ft_strlen(env->val);
			if (write(fd_out, env->val, size) < 0)
				return (1);
			if (write(fd_out, "\n", 1) < 0)
				return (1);
		}
		env = env->next;
	}
	return (0);
}
