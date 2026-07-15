/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:00:54 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/15 10:20:34 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free all 'exec' nodes and their attributes
 *
 * @param exec Structure containing every data needed to execute execve()
 */
void	free_exec(t_exec *exec)
{
	if (exec->absolute_cmd)
		free(exec->absolute_cmd);
	free_ar(exec->args);
	free_ar(exec->env);
	free(exec);
}

/**
 * @brief Free the pid list given
 *
 * @param pid_list List of the pids of every command in a pipe command
 */
void	free_pid_list(t_pid_list *pid_list)
{
	t_pid_list	*tmp;

	while (pid_list)
	{
		tmp = pid_list->next;
		free(pid_list);
		pid_list = tmp;
	}
}

t_pid_list	*get_last_pid(t_pid_list *pid_list)
{
	t_pid_list	*last;

	last = pid_list;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}
