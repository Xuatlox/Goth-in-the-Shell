/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:19:28 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/15 10:30:06 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Waits for all pids in the list
 *
 * @param pids List of pids to wait for
 */
static void	wait_pids(t_pid_list *pids, int *status)
{
	int	ret;

	ret = 0;
	sig_exec();
	while (pids)
	{
		if (pids->pid)
		{
			waitpid(pids->pid, &ret, 0);
			if (WIFEXITED(ret))
				*status = WEXITSTATUS(ret);
			if (WIFSIGNALED(ret))
				*status = WTERMSIG(ret) + 128;
		}
		else
			*status = pids->ret;
		pids = pids->next;
	}
}

void	pids_loop(t_token **tokens, t_env **env, t_pid_list *head)
{
	t_token		**cpy;
	t_pid_list	*pids;

	pids = head;
	cpy = tokens;
	while (cpy && *cpy)
	{
		if ((*cpy)->cmd && (*cpy)->cmd->str)
			pids->ret = dispatch(cpy, env, head, 1);
		jump_next_token(cpy);
		if (cpy && *cpy)
			pids->next = ft_calloc(1, sizeof(t_pid_list));
		if (!pids->next)
			break ;
		else
			pids = pids->next;
	}
}

/**
 * @brief Executes all the token list.
 *
 * @param tokens List of tokens to be executed
 * @param env List of environmental variables
 * @return Exit status of the last command of the token list
 */
static int	exec_all(t_token **tokens, t_env **env)
{
	int			ret;
	t_pid_list	*head;

	head = ft_calloc(1, sizeof(t_pid_list));
	if (!head)
		return (1);
	ret = 0;
	pids_loop(tokens, env, head);
	close_fds(*tokens);
	wait_pids(head, &ret);
	free_pid_list(head);
	return (ret);
}

/**
 * @brief Open a pipe between each token and stores them in the token list
 *
 * @param tokens List of tokens to be executed
 * @return 0 on success, 1 if an error occurred
 */
static int	pipe_all(t_token **tokens)
{
	int		fds[2];
	t_token	**cpy;

	cpy = tokens;
	while ((*cpy)->next)
	{
		if (pipe(fds))
		{
			free_tokens(tokens);
			return (1);
		}
		if ((*cpy)->outfile < 0)
			(*cpy)->outfile = fds[1];
		else
			close(fds[1]);
		if ((*cpy)->next->infile < 0)
			(*cpy)->next->infile = fds[0];
		else
			close(fds[0]);
		cpy = &(*cpy)->next;
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
int	exec_pipe(t_token **tokens, t_env **env)
{
	int		ret;
	int		failed;

	if (!tokens || !*tokens)
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
