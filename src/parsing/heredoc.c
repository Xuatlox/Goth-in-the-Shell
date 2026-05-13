/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:30:45 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/13 11:27:02 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int heredoc(char *delimiter, int fd[2], t_env *env)
{
	char	*input;

	close(fd[0]);
	while (1)
	{
		input = readline("> ");
		if (g_sig_ind == SIGINT)
			break ;
		if (input == NULL)
		{
			error_heredoc(delimiter);
			break ;
		}
		if (ft_strcmp(input, delimiter) == 0)
			break ;
		(void)env;
		write(fd[1], &input, strlen(input));
		free(input);
	}
	free(delimiter);
	if (input)
		free(input);
	close(fd[1]);
	exit(0);
}

int	pipe_heredoc(char *delimiter, t_env *env)
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
		heredoc(delimiter, fd, env);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}
