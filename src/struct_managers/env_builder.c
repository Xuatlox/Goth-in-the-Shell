/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:25:08 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/19 14:09:52 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static int	get_val_name(char **name, char **val, char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		++i;
	if (env_var[i + 1])
		*val = ft_strdup(&env_var[i + 1]);
	if (!*val)
		return (1);
	env_var[i] = 0;
	*name = ft_strdup(env_var);
	if (!*name)
	{
		free(*val);
		return (1);
	}
	return (0);
}

t_env	*build_env(char **envp)
{
	char	*val;
	char	*name;
	int		fail;
	t_env	*env;
	t_env	*ret;

	env = ft_calloc(1, sizeof(t_env));
	while (*envp)
	{
		fail = get_val_name(&name, &val, *envp);
		if (fail || add_env(env, name, val))
		{
			free_env(env);
			return (NULL);
		}
		++envp;
	}
	ret = env->next;
	free(env);
	return (ret);
}

t_env	*new_env(char *name, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->val = value;
	return (new);
}

void	free_env(t_env *env)
{
	t_env		*tmp_env;

	while (env)
	{
		tmp_env = env;
		if (env->name)
			free(env->name);
		if (env->val)
			free(env->val);
		env = env->next;
		free(tmp_env);
	}
}
