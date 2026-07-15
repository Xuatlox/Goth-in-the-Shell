/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/15 11:42:44 by mcrenn           ###   ########.fr       */
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
static int	check_line(char *line)
{
	size_t	i;

	i = 0;
	if (line && line[i])
		add_history(line);
	while (line[i] && ft_isspace(line[i]))
		++i;
	if (!line[i])
	{
		free(line);
		return (1);
	}
	return (0);
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

void	minishell(char *line, t_minishell *shell)
{
	t_status	status;

	status = SUCCESS;
	parsing(line, &status, shell);
	shell->old_error_code = (int)status;
	if (status == SUCCESS)
		shell->old_error_code = execute(&shell->tkn_node, &shell->env);
	close_fds(shell->tkn_node);
	free_tokens(&shell->tkn_node);
	status = SUCCESS;
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	sig_inter();
	ft_bzero(&shell, sizeof(t_minishell));
	shell.env = build_env(envp);
	while (1)
	{
		line = readline("goth_in_the_shell> ");
		check_sig(&shell.old_error_code);
		if (!line)
		{
			free_env(shell.env);
			rl_clear_history();
			return (shell.old_error_code);
		}
		if (check_line(line))
			continue ;
		minishell(line, &shell);
	}
	return (0);
}
