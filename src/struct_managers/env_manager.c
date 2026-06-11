/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/11 11:01:06 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of nodes in the 'env' list
 *
 * @param env List of environmental variables
 * @return Number of nodes in env, or 0 if env is NULL
 */
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

/**
 * @brief Searches for a pointer to the value of the 'name' variable in env
 *
 * @param env List of environmental variables
 * @param name Name of the variable we want to get
 * @return Pointer to the value of the variable 'name', or NULL if not found
 */
char	**get_env(t_env *env, const char *name)
{
	size_t	size;

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

/**
 * @brief Sets the value of the 'var_name' variable to 'new_val', if existing
 *
 * @param var_name Name of the variable we want to change
 * @param new_val New value to set to the 'var_name' variable in env
 * @param env List of environmental variables
 */
void	set_env(char *var_name, char *new_val, t_env *env)
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

/**
 * @brief Adds a new variable at the end of 'env'
 *
 * @param env List of environmental variables
 * @param name Name of the variable to add
 * @param value Value of the variable to add
 * @return 0 on success, 1 if an error occurred
 */
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
	{
		set_env(name, value, env);
		free(name);
	}
	else
	{
		new = new_env(name, value);
		while (env->next)
			env = env->next;
		env->next = new;
	}
	return (0);
}

/**
 * @brief Increases the SHLVL variable in env by 1, if existing
 *
 * @param env List of environmental variables
 */
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
