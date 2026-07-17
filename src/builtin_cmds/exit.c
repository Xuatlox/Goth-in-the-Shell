/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:37:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/17 10:44:50 by mcrenn           ###   ########.fr       */
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
static void	exit_default(t_token **token, t_env *env, t_pid_list *pids)
{
	free_env(env);
	free_tokens(token);
	free_pid_list(pids);
	rl_clear_history();
	exit(2);
}

/**
 * @brief Converts the code from str to a long long int
 *
 * @param str String containing the code to convert
 * @return The converted code, or 2 if it exceeds the long long range
 */
static long	get_code(const char *str)
{
	size_t	i;
	long	code;
	int		sign;

	sign = 1;
	code = 0;
	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (*str == '+' || *str == '-')
		sign = (*(str + i++) % 43) * -1 + 1;
	while (ft_isdigit(str[i]))
	{
		if (code * sign <= (LONG_MAX - ((*(str + i)) - '0')) / 10
			&& code * sign >= (LONG_MIN + ((*(str + i)) - '0')) / 10)
			code = code * 10 + (*(str + i++) - '0');
		else
		{
			write(2, "goth_in_the_shell: ", 19);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 28);
			return (2);
		}
	}
	return ((long)sign * code);
}

/**
 * @brief Mimics the behavior of the exit command in bash
 *
 * @param token List of tokens to free before exit
 * @param env List of environmental variables to free before exit
 * @param is_piped Indicates if the command is in a pipe (1) or not (0)
 * @return 1 if an error occurred
 */
int	exec_exit(t_token **token, t_env *env, int is_piped, t_pid_list *pids)
{
	long long	code;

	if (!is_piped)
		write(2, "exit\n", 5);
	if (!(*token)->cmd->next || !is_num((*token)->cmd->next->str))
	{
		if (is_piped)
			return (2);
		exit_default(token, env, pids);
	}
	if ((*token)->cmd->next->next)
	{
		write(2, "goth_in_the_shell: exit: too many arguments\n", 44);
		return (1);
	}
	code = get_code((*token)->cmd->next->str);
	code %= 256;
	if (is_piped)
		return ((int) code);
	free_pid_list(pids);
	free_env(env);
	free_tokens(token);
	rl_clear_history();
	exit((int) code);
}
