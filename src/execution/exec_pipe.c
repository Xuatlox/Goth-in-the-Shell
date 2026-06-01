/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:19:28 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 10:48:05 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes all the token list and waits for every process to end.
 *
 * @param tokens List of tokens to be executed
 * @param env List of environmental variables
 * @return Exit status of the last command of the token list
 */
static int	exec_all(t_token *tokens, t_env **env)
{
	int			ret;
	t_pid_list	*pids;
	t_pid_list	*head;

	pids = ft_calloc(1, sizeof(t_pid_list));
	head = pids;
	while (tokens)
	{
		pids->pid = dispatch(tokens, env, &pids->pid);
		tokens = jump_next_token(tokens);
		pids->next = ft_calloc(1, sizeof(t_pid_list));
		pids = pids->next;
	}
	close_fds(tokens);
	pids = head;
	sig_exec();
	while (pids)
	{
		waitpid(pids->pid, &ret, 0);
		pids = pids->next;
	}
	free_pid_list(head);
	ret = WEXITSTATUS(ret);
	return (ret);
}

/**
 * @brief Open a pipe between each token and stores them in the token list
 *
 * @param tokens List of tokens to be executed
 * @return 0 on success, 1 if an error occurred
 */
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

/**
 * @brief Executes every subfunctions needed to execute the piped commands
 *
 * @param tokens List of tokens to be executed
 * @param env List of environmental variables
 * @return The exit status of the piped commands sent
 */
int	exec_pipe(t_token *tokens, t_env **env)
{
	int		ret;
	int		failed;

	if (!tokens)
		return (0);
	failed = pipe_all(tokens);
	if (failed)
	{
		perror("goth_in_the_shell: pipe_all");
		return (1);
	}
	ret = exec_all(tokens, env);
	return (ret);
}
