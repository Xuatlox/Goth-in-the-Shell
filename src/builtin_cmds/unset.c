/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:51:12 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/18 11:35:18 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds the variable before 'to_find' in env
 *
 * @param env List of environmental variables
 * @param to_find Name of the variable following the one wanted in env
 * @param size Size of 'to_find'
 * @return The env variable before 'to_find' in env, NULL if not found
 */
static t_env	*find_prev(t_env *env, const char *to_find, const size_t size)
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

/**
 * @brief Free the head of the env list and sets the head to the next node
 *
 * @param env List of environmental variables
 */
static void	unset_head(t_env **env)
{
	t_env	*node;

	node = (*env)->next;
	free((*env)->name);
	free((*env)->val);
	free(*env);
	*env = node;
}

/**
 * @brief Free the 'name' variable in env and links back all nodes together
 *
 * @param env List of environmental variables
 * @param name Name of the variable to be removed
 * @param size Size of name
 */
static void	unset_node(t_env **env, const char *name, const size_t size)
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

/**
 * @brief Mimics the behavior of the unset command in bash
 *
 * @param args Arguments following the 'unset' command
 * @param env List of environmental variables
 * @param is_piped Indicates if the command is in a pipe (1) or not (0)
 * @return 0 on success, 1 if an error occurred
 */
int	exec_unset(const t_command *args, t_env **env, int is_piped)
{
	size_t	size;

	if (!is_piped)
		return (0);
	if (!env || !*env)
		return (1);
	while (args)
	{
		size = ft_strlen(args->str);
		if (!ft_strncmp((*env)->name, args->str, size + 1))
			unset_head(env);
		else
			unset_node(env, args->str, size);
		args = args->next;
	}
	return (0);
}
