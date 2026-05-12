/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:19:28 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/11 10:45:47 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_all(t_token *tokens, t_env *env)
{
	int		ret;

	ret = 127;
	while (tokens)
	{
		ret = dispatch(tokens, env);
		tokens = jump_next_token(tokens);
	}
	return (ret);
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
	int		ret;
	int		failed;

	if (!tokens)
		return (127);
	failed = pipe_all(tokens);
	if (failed)
		return (0);
	ret = exec_all(tokens, env);
	return (ret);
}
