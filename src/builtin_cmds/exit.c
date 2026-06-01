/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:37:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 11:11:48 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether str contains a valid exit code or not
 *
 * @param str First argument given after the 'exit' command
 * @return 1 if str is valid, else 0
 */
static int	is_num(const char *str)
{
	if (!str)
		return (0);
	if (*str == '-' || *str == '+')
		++str;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		++str;
	}
	return (1);
}

/**
 * @brief Exits the program with the default error code (2)
 *
 * @param token List of tokens to free before exit
 * @param env List of environmental variables to free before exit
 */
static void	exit_default(t_token *token, t_env *env)
{
	size_t	size;

	if (token->cmd->next)
	{
		size = ft_strlen(token->cmd->next->str);
		write(2, "goth_in_the_shell: exit: ", 25);
		write(2, token->cmd->next->str, size);
		write(2, "\n", 1);
	}
	free_env(env);
	free_tokens(token);
	rl_clear_history();
	exit(2);
}

/**
 * @brief Mimics the behavior of the exit command in bash
 *
 * @param token List of tokens to free before exit
 * @param env List of environmental variables to free before exit
 * @return 1 if an error occurred
 */
int	exec_exit(t_token *token, t_env *env)
{
	int		code;

	write(1, "exit\n", 5);
	if (!token->cmd->next || !is_num(token->cmd->next->str))
		exit_default(token, env);
	if (token->cmd->next->next)
	{
		write(2, "goth_in_the_shell: exit: too many arguments\n", 44);
		return (1);
	}
	code = ft_atoi(token->cmd->next->str);
	free_env(env);
	free_tokens(token);
	rl_clear_history();
	exit(code % 256);
}
