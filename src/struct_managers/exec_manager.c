/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:00:54 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 10:48:05 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_exec *exec)
{
	int	i;

	if (exec->absolute_cmd)
		free(exec->absolute_cmd);
	if (exec->args)
	{
		i = 0;
		while (exec->args[i])
		{
			free(exec->args[i]);
			++i;
		}
		free(exec->args);
	}
	if (exec->env)
	{
		i = 0;
		while (exec->env[i])
		{
			free(exec->env[i]);
			++i;
		}
		free(exec->env);
	}
	free(exec);
}

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
