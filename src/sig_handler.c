/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:36:40 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/27 17:56:40 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

extern int	sig_ind;

static void sig_handler(int sig)
{
	sig_ind = sig;
}

int detect_sig(void)
{
	struct sigaction	act;
	sigset_t			set;

	if (sigemptyset(&set) < 0)
		return (0);
	if (sigaddset(&set, SIGQUIT) < 0)
		return (0);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handler;
	sigaction(SIGINT, &act, NULL);
	return (1);
}
