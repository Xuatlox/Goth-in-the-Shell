/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:19:28 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/07 14:07:44 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	wait_all(const pid_t *pid)
{
	int		status;

	while (*pid)
	{
		waitpid(*pid, &status, 0);
		++pid;
	}
	status = WEXITSTATUS(status);
	return (status);
}

void	pipe_child_proc(t_token *tokens, t_env *env)
{
	int	ret;

	ret = dispatch(tokens, env);
	close_fds(tokens);
	free_tokens(tokens);
	free_env(env);
	exit(ret);
}

static int	exec_all(t_token *tokens, t_env *env, pid_t **pid)
{
	int		i;

	i = 0;
	while (tokens)
	{
		(*pid)[i] = fork();
		if ((*pid)[i] < 0)
		{
			wait_all(*pid);
			close_fds(tokens);
			free_tokens(tokens);
			free(*pid);
			return (0);
		}
		if ((*pid)[i] == 0)
		{
			free(*pid);
			pipe_child_proc(tokens, env);
		}
		++i;
		tokens = jump_next_token(tokens);
	}
	return (1);
}

static int	pipe_all(t_token *tokens)
{
	int	fds[2];

	while (tokens->next)
	{
		if (pipe(fds))
		{
			free_tokens(tokens);
			return (1);
		}
		if (tokens->outfile < 0)
			tokens->outfile = fds[1];
		else
			close(fds[1]);
		if (tokens->next->infile < 0)
			tokens->next->infile = fds[0];
		else
			close(fds[0]);
		tokens = tokens->next;
	}
	return (0);
}

int	exec_pipe(t_token *tokens, t_env *env)
{
	pid_t	*pid;
	int		size;
	int		ret;
	int		failed;

	size = tokens_len(tokens);
	pid = ft_calloc(size + 1, sizeof(pid_t));
	if (!pid)
		return (0);
	failed = pipe_all(tokens);
	if (!failed)
		failed = !exec_all(tokens, env, &pid);
	if (failed)
	{
		free(pid);
		return (0);
	}
	ret = wait_all(pid);
	free(pid);
	return (ret);
}
