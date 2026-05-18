/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/18 13:39:43 by mcrenn           ###   ########.fr       */
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
	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.env = build_env(envp);
	status = SUCCESS;
	while (1)
	{
		line = readline("goth_in_the_shell> ");
		if (line[0] != 0)
			add_history(line);
		parsing(line, &status, &minishell);
		minishell.old_error_code = (int)status;
		if (!status)
			minishell.old_error_code = execute(minishell.tkn_node, minishell.env);
		status = SUCCESS;
		minishell.tkn_node = NULL;
	}
	rl_clear_history();
}
