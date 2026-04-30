/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:36:40 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/30 14:20:19 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

extern volatile sig_atomic_t	sig_ind;

static void sig_handler(int sig)
{
	sig_ind = sig;
}

int detect_sig(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handler;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
