/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 10:48:05 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_size(const t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		++size;
		env = env->next;
	}
	return (size);
}

char	**get_env(t_env *env, const char *name)
{
	int	size;

	if (!name || !env)
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

	if (!env)
		return ;
	var_val = get_env(env, var_name);
	if (var_val)
	{
		if (*var_val)
			free(*var_val);
		*var_val = new_val;
	}
}

int	add_env(t_env *env, char *name, char *value)
{
	char	**get;
	t_env	*new;

	if (!env)
		env = new_env(name, value);
	if (!env)
		return (1);
	get = get_env(env, name);
	if (get)
		set_env(name, value, env);
	else
	{
		new = new_env(name, value);
		while (env->next)
			env = env->next;
		env->next = new;
	}
	return (0);
}

void	up_shlvl(t_env *env)
{
	int		conv;
	char	**sh_lvl;

	sh_lvl = get_env(env, "SHLVL");
	if (!sh_lvl)
		return ;
	conv = ft_atoi(*sh_lvl);
	if (!conv)
		return ;
	free(*sh_lvl);
	*sh_lvl = ft_itoa(conv + 1);
}
