/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/12 15:09:27 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_ind = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_status	status;
	t_token		*tkn_node;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = build_env(envp);
	status = SUCCESS;
	while (1)
	{
		line = readline("Write input: ");
		if (line[0] != 0)
			add_history(line);
		tkn_node = parsing(line, &status, env);
		execute(tkn_node, env);
	}
	rl_clear_history();
}
