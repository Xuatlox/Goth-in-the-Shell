/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:30:45 by mcrenn            #+#    #+#             */
/*   Updated: 2026/07/15 11:24:09 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	qte_remove(char **delimiter)
{
	size_t	count;

	count = quote_counter(*delimiter);
	if (count > 0)
	{
		str_without_qte(delimiter, count);
		return (NO_EXPAND);
	}
	else
		return (EXPAND);
}

int	heredoc_manager(char *input, char *delimiter)
{
	if (g_sig_ind == SIGINT)
		return (0);
	if (input == NULL)
	{
		error_heredoc(delimiter);
		return (0);
	}
	if (ft_strcmp(input, delimiter) == 0)
		return (0);
	return (1);
}

static int	heredoc(char *delimiter, int fd[2], t_minishell *shell)
{
	char		*input;
	t_status	status;
	t_expand	expand;

	status = SUCCESS;
	rl_clear_history();
	sig_inter_child_heredoc();
	expand = qte_remove(&delimiter);
	while (1)
	{
		input = readline("> ");
		if (heredoc_manager(input, delimiter) == 0)
			break ;
		check_expand(&input, shell, &status, expand);
		ft_putendl_fd(input, fd[1]);
		free(input);
	}
	free(delimiter);
	if (input)
		free(input);
	lst_clear_tkn(&shell->tkn_node);
	free_env(shell->env);
	close(fd[1]);
	rl_clear_history();
	exit(0);
}

int	pipe_heredoc(char *delimiter, t_minishell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		heredoc(delimiter, fd, shell);
	}
	close(fd[1]);
	sig_inter_heredoc();
	waitpid(pid, NULL, 0);
	sig_inter();
	return (fd[0]);
}
