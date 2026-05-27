/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:36:40 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/27 16:43:16 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void sigint_inter_handler(int sig)
{
	(void) sig;
	g_sig_ind = SIGINT;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_inter(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_inter_handler;
	if (sigaction(SIGINT, &act, NULL) < 0)
		perror("goth_in_the_shell: sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("goth_in_the_shell: signal");
}

static void sigint_exec_handler(int sig)
{
	(void) sig;
	g_sig_ind = SIGINT;
	write(2, "\n", 1);
}

static void sigquit_exec_handler(int sig)
{
	(void) sig;
	g_sig_ind = SIGQUIT;
	write(2, "Quit\n", 5);
}

void	sig_exec(void)
{
	struct sigaction	act_int;
	struct sigaction	act_quit;

	ft_bzero(&act_int, sizeof(act_int));
	ft_bzero(&act_quit, sizeof(act_quit));
	act_int.sa_handler = &sigint_exec_handler;
	act_quit.sa_handler = &sigquit_exec_handler;
	if (sigaction(SIGINT, &act_int, NULL) < 0
		|| sigaction(SIGQUIT, &act_quit, NULL) < 0)
		perror("goth_in_the_shell: sigaction");
}
