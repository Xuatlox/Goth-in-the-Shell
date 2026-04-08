/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:20:20 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/08 16:52:00 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

char	**get_env(t_env *env, const char *name)
{
	int	size;

	if (!name)
		return (NULL);
	size = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->name, name, size + 1))
			return (&env->val);
		env = env->next;
	}
	return (NULL);
}
