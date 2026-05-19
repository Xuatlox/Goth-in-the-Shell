/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:03:04 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/19 13:43:22 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_proc(t_env *env, t_token *token, t_exec *exec)
{
	int		dup_ret;

	dup_ret = dup2(token->infile, STDIN_FILENO);
	if (dup_ret != -1)
		dup_ret = dup2(token->outfile, STDOUT_FILENO);
	close_fds(token);
	free_env(env);
	free_tokens(token);
	if (dup_ret != -1)
		execve(exec->absolute_cmd, exec->args, exec->env);
	perror("goth_in_the_shell: child_proc");
	free_exec(exec);
	exit(1);
}

int	manage_child(t_env *env, t_token *token, t_exec *exec)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid < 0)
	{
		free_exec(exec);
		return (1);
	}
	if (pid == 0)
		child_proc(env, token, exec);
	close_fds(token);
	waitpid(pid, &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	free_exec(exec);
	return (exit_code);
}
