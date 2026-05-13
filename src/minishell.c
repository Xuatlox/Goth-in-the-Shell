/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/13 16:16:41 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_ind = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	minishell;
	t_status	status;

	(void)argc;
	(void)argv;
	ft_bzero(&minishell, sizeof(minishell));
	minishell.env = build_env(envp);
	status = SUCCESS;
	while (1)
	{
		line = readline("goth_in_the_shell> ");
		if (line[0] != 0)
			add_history(line);
		parsing(line, &status, &minishell);
		execute(minishell.tkn_node, minishell.env);
	}
	rl_clear_history();
}
