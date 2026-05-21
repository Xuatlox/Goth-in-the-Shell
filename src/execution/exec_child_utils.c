/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:03:04 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/20 15:14:28 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_proc(t_env *env, t_token *token, t_exec *exec)
{
	int		ret;

	ret = dup2(token->infile, STDIN_FILENO);
	if (ret != -1)
		ret = dup2(token->outfile, STDOUT_FILENO);
	close_fds(token);
	free_env(env);
	free_tokens(token);
	if (ret != -1)
		ret = execve(exec->absolute_cmd, exec->args, exec->env);
	if (ret == -1)
		perror(exec->absolute_cmd);
	free_exec(exec);
	exit(1);
}

pid_t	manage_child(t_env *env, t_token *token, t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		free_exec(exec);
		return (1);
	}
	if (pid == 0)
		child_proc(env, token, exec);
	free_exec(exec);
	return (pid);
}
