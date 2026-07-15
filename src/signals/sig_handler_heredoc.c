/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:45:53 by mcrenn            #+#    #+#             */
/*   Updated: 2026/07/15 11:45:55 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sigint_inter_heredoc_handler(int sig, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;
	(void)sig;
	g_sig_ind = SIGINT;
	write(2, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	close(0);
}

void	sig_inter_child_heredoc(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_sigaction = &sigint_inter_heredoc_handler;
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		perror("goth_in_the_shell: sigaction");
		return ;
	}
	action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &action, NULL) < 0)
		perror("goth_in_the_shell: sigaction");
}

void	sig_inter_heredoc(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &action, NULL) < 0
		|| sigaction(SIGINT, &action, NULL) < 0)
		perror("goth_in_the_shell: sigaction");
}
