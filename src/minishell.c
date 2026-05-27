/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/27 16:44:00 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_ind = 0;

int	check_line(char *line, t_env *env)
{
	if (line)
	{
		if (line[0] != 0)
			add_history(line);
		return (0);
	}
	free_env(env);
	rl_clear_history();
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	shell;
	t_status	status;

	(void)argc;
	(void)argv;
	sig_inter();
	ft_bzero(&shell, sizeof(t_minishell));
	shell.env = build_env(envp);
	status = SUCCESS;
	line = NULL;
	while (1)
	{
		line = readline("goth_in_the_shell> ");
		if (check_line(line, shell.env))
			return (0);
		parsing(line, &status, &shell);
		shell.old_error_code = (int)status;
		if (!status)
			shell.old_error_code = execute(shell.tkn_node, &shell.env);
		status = SUCCESS;
		shell.tkn_node = NULL;
	}
}
