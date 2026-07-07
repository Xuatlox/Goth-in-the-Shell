/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:36:40 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/30 14:06:08 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/**
 * @brief Resets readline to a new line after SIGINT in interactive mode
 *
 * @param sig Signal identifier
 */
static void sigint_inter_handler(int sig, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;
	(void)sig;
	g_sig_ind = SIGINT;
	write(2, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void sigint_inter_heredoc_handler(int sig, siginfo_t *info, void *other)
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


/**
 * @brief Sets SIGINT and SIGQUIT behaviors for interactive mode
 */
void	sig_inter(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_sigaction = &sigint_inter_handler;
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		perror("goth_in_the_shell: sigaction");
		return ;
	}
	action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &action, NULL) < 0)
		perror("goth_in_the_shell: sigaction");
}

void	sig_inter_child_heredoc()
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

/**
 * @brief Go to new line after SIGINT during execution
 *
 * @param sig Signal identifier
 */
static void sigint_exec_handler(int sig)
{
	(void) sig;
	g_sig_ind = SIGINT;
	write(2, "\n", 1);
}

/**
 * @brief Prints "Quit" and go to new line after SIGQUIT during execution
 *
 * @param sig Signal identifier
 */
static void sigquit_exec_handler(int sig)
{
	(void) sig;
	g_sig_ind = SIGQUIT;
	write(2, "Quit\n", 5);
}

/**
 * @brief Sets SIGINT and SIGQUIT behaviors for execution
 */
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
