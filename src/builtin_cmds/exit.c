/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:37:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/15 11:12:55 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints an error message in STDERR
 *
 * @param arg Argument given after the 'exit' command
 * @param msg Message to write describing the error
 */
static void	print_exit_error(const char *arg, const char *msg)
{
	size_t	size;

	write(2, "goth_in_the_shell: exit: ", 25);
	size = ft_strlen(arg);
	write(2, arg, size);
	write(2, ": ", 2);
	size = ft_strlen(msg);
	write(2, msg, size);
	write(2, "\n", 1);
}

/**
 * @brief Checks whether str contains a valid exit code or not
 *
 * @param str First argument given after the 'exit' command
 * @return 1 if str is valid, else 0
 */
static int	is_num(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		++str;
	if (!str[i])
	{
		print_exit_error(str, "numeric argument required");
		return (0);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			print_exit_error(str, "numeric argument required");
			return (0);
		}
		++i;
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
	free_env(env);
	free_tokens(token);
	rl_clear_history();
	exit(2);
}

/**
 * @brief Converts the code from str to a long long int
 *
 * @param str String containing the code to convert
 * @return The converted code, or 2 if it exceeds the long long range
 */
static long long	get_code(const char *str)
{
	long long	code;
	long long	sign;

	sign = 1;
	code = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		if (code > 922337203685477580
			|| (code == 922337203685477580
			&& ((sign == 1 && *str > '7') || (sign == -1 && *str > '8'))))
			return (2);
		code = code * 10 + *str - '0';
		++str;
	}
	return (sign * code);
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
	long long	code;

	write(1, "exit\n", 5);
	if (!token->cmd->next || !is_num(token->cmd->next->str))
		exit_default(token, env);
	if (token->cmd->next->next)
	{
		write(2, "goth_in_the_shell: exit: too many arguments\n", 44);
		return (1);
	}
	code = get_code(token->cmd->next->str);
	code %= 256;
	free_env(env);
	free_tokens(token);
	rl_clear_history();
	exit((int) code);
}
