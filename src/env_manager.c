/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/30 11:23:35 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

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
	{
		free(*var_val);
		*var_val = new_val;
	}
}

void	add_env(t_env *env, char *name, char *value)
{
	char	**get;
	t_env	*new;

	get = get_env(env, name);
	if (get)
	{
		if (*get)
			free(*get);
		*get = value;
	}
	else
	{
		new = malloc(sizeof(t_env));
		new->name = name;
		new->val = value;
		new->next = NULL;
		while (env->next)
			env = env->next;
		env->next = new;
	}
}

void	free_env_tokens(t_env *env, t_token *token)
{
	t_env		*tmp_env;
	t_command	*tmp_cmd;

	while (env)
	{
		tmp_env = env->next;
		free(env->name);
		free(env->val);
		free(env);
		env = tmp_env;
	}
	while (token->cmd)
	{
		tmp_cmd = token->cmd->next;
		free(token->cmd->str);
		free(token->cmd);
		token->cmd = tmp_cmd;
	}
	free(token);
}
