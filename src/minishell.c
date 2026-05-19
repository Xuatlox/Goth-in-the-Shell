/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/18 14:36:01 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_ind = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	shell;
	t_status	status;

	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_minishell));
	shell.env = build_env(envp);
	status = SUCCESS;
	while (1)
	{
		line = readline("goth_in_the_shell> ");
		if (line[0] != 0)
			add_history(line);
		parsing(line, &status, &shell);
		shell.old_error_code = (int)status;
		if (!status)
			shell.old_error_code = execute(shell.tkn_node, &shell.env);
		status = SUCCESS;
		shell.tkn_node = NULL;
	}
}
