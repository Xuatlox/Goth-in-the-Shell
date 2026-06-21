/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/19 13:16:39 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_ind = 0;

/**
 * @brief Checks 'line' and eventually adds it to history
 *
 * @param line readline() return value
 * @param env List of environmental variables
 * @return 0 if 'line' is correct, else 1
 */
static int	check_line(char **line, t_env *env)
{
	int	i;

	while (*line)
	{
		i = 0;
		if (*line != 0)
			add_history(*line);
		while (ft_isspace((*line)[i]))
			++i;
		if ((*line)[i])
			return (0);
		*line = readline("goth_in_the_shell> ");
	}
	free_env(env);
	rl_clear_history();
	return (1);
}

/**
 * @brief Checks if a signal occurred and sets the corresponding return value
 * if yes
 *
 * @param ret Pointer to the return value to eventually change
 */
static void	check_sig(int *ret)
{
	if (g_sig_ind)
	{
		*ret = 128 + g_sig_ind;
		g_sig_ind = 0;
	}
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
		if (check_line(&line, shell.env))
			return (shell.old_error_code);
		check_sig(&shell.old_error_code);
		parsing(line, &status, &shell);
		shell.old_error_code = (int)status;
		if (status == SUCCESS)
			shell.old_error_code = execute(shell.tkn_node, &shell.env);
		status = SUCCESS;
		shell.tkn_node = NULL;
	}
}
