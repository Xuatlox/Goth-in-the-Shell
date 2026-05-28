/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:03:04 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/28 14:16:53 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	reset_sig(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, NULL)
		|| sigaction(SIGQUIT, &sa, NULL))
	{
		perror("goth_in_the_shell: sigaction");
		return (1);
	}
	return (0);
}

static void	print_cmd_not_found(t_exec *exec)
{
	size_t	size;

	write(2, "goth_in_the_shell: ", 19);
	size = ft_strlen(exec->args[0]);
	write(2, exec->args[0], size);
	write(2, ": command not found\n", 20);
}

static void	child_proc(t_env *env, t_token *token, t_exec *exec)
{
	int		ret;

	if (reset_sig())
	{
		perror("goth_in_the_shell: sigaction");
		exit(1);
	}
	ret = dup2(token->infile, STDIN_FILENO);
	if (ret != -1)
		ret = dup2(token->outfile, STDOUT_FILENO);
	close_fds(token);
	free_env(env);
	free_tokens(token);
	if (ret != -1)
		ret = execve(exec->absolute_cmd, exec->args, exec->env);
	if (ret == -1)
	{
		print_cmd_not_found(exec);
		ret = 127;
	}
	else
		ret = 1;
	free_exec(exec);
	exit(ret);
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
