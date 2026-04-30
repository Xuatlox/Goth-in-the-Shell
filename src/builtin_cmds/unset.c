/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:51:12 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/30 14:02:03 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	*find_prev(t_env *env, const char *to_find, const int size)
{
	if (!env)
		return (NULL);
	while (env->next)
	{
		if (!ft_strncmp(env->next->name, to_find, size + 1))
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	unset_head(t_env **env)
{
	t_env	*node;

	node = (*env)->next;
	free((*env)->name);
	free((*env)->val);
	free(*env);
	*env = node;
}

static void	unset_node(t_env **env, const char *name, int size)
{
	t_env	*prev_node;
	t_env	*node;
	t_env	*next_node;

	prev_node = find_prev(*env, name, size);
	if (!prev_node)
		return ;
	node = prev_node->next;
	next_node = node->next;
	free(node->name);
	free(node->val);
	free(node);
	prev_node->next = next_node;
}

int	exec_unset(const t_command *args, t_env *env)
{
	int		size;

	if (!env)
		return (1);
	while (args)
	{
		size = ft_strlen(args->str);
		if (!ft_strncmp(env->name, args->str, size + 1))
			unset_head(&env);
		else
			unset_node(&env, args->str, size);
		args = args->next;
	}
	return (0);
}
