/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/20 12:55:25 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exec_env(const t_command *args, const int fd_out, const t_env *env)
{
	int	size;

	if (!args)
	{
		printf("No arguments allowed for env\n");
		return (0);
	}
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
	return (1);
}
