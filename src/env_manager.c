/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:16:26 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/10 15:16:30 by ansimonn         ###   ########.fr       */
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

void	set_env(const char *var_name, char *new_val, t_env *env)
{
	char	**var_val;

	var_val = get_env(env, var_name);
	if (var_val)
		*var_val = new_val;
}
