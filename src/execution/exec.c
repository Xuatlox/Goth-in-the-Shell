/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/03 16:24:26 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *
 * @brief Sends the program to the associated function to execute the command
 *
 * @param token List of tokens to be executed
 * @param env List of environmental variables
 * @param pid Pointer to the eventual pid of the command to be executed
 * @return Return value of the function executed
 */
int	dispatch(t_token *token, t_env **env, pid_t *pid)
{
	int		ret;

	ret = 0;
	if (!ft_strncmp(token->cmd->str, "cd", 3))
		ret = exec_cd(token->cmd->next, token->outfile, *env);
	else if (!ft_strncmp(token->cmd->str, "export", 7))
		ret = exec_export(token->cmd->next, token->outfile, env);
	else if (!ft_strncmp(token->cmd->str, "pwd", 4))
		ret = exec_pwd(token->outfile, *env);
	else if (!ft_strncmp(token->cmd->str, "env", 4))
		ret = exec_env(token->outfile, *env);
	else if (!ft_strncmp(token->cmd->str, "echo", 5))
		ret = exec_echo(token->cmd->next, token->outfile);
	else if (!ft_strncmp(token->cmd->str, "unset", 6))
		ret = exec_unset(token->cmd->next, env);
	else if (!ft_strncmp(token->cmd->str, "exit", 5))
		ret = exec_exit(token, *env);
	else
		*pid = exec_child(token, *env);
	return (ret);
}

/**
 *
 * @brief Prints an error message and returns the associated code
 *
 * @param cmd Invalid command written by the user
 * @param msg Error message to print
 * @return Error code associated to 'msg'
 */
static int	print_cmd_error(char *cmd, char *msg)
{
	size_t	size;

	size = ft_strlen(cmd);
	write(2, "goth_in_the_shell: ", 19);
	write(2, cmd, size);
	size = ft_strlen(msg);
	write(2, msg, size);
	if (!ft_strncmp(msg, ": Permission denied\n", 21)
		|| !ft_strncmp(msg, ": Is a directory\n", 18))
		return (126);
	if (!ft_strncmp(msg, ": filename argument required\n", 29))
		return (2);
	if (!ft_strncmp(msg, ": No such file or directory\n", 29))
		return (127);
	return (1);
}

static int	is_directory(char *str)
{
	struct stat stats;

	stat(str, &stats);
	if (*str == '/' && S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

/**
 *
 * @brief Initializes the first command's infile and the last command's outfile
 * and checks the first command argument
 *
 * @param tokens List of tokens to be executed
 */
static int	init_check(t_token *tokens)
{
	int	ret;

	if (!tokens || !tokens->cmd || !tokens->cmd->str)
		return (1);
	if (tokens->infile == -1)
		tokens->infile = STDIN_FILENO;
	while (tokens->next)
		tokens = tokens->next;
	if (tokens->outfile == -1)
		tokens->outfile = STDOUT_FILENO;
	ret = 0;
	if (!ft_strncmp(tokens->cmd->str, ".", 2))
		ret = print_cmd_error(tokens->cmd->str, ": filename argument required\n");
	else if (is_directory(tokens->cmd->str))
		ret = print_cmd_error(tokens->cmd->str, ": Is a directory\n");
	else if ((*tokens->cmd->str == '/' || *tokens->cmd->str == '.')
		&& access(tokens->cmd->str, F_OK) < 0)
		ret = print_cmd_error(tokens->cmd->str, ": No such file or directory\n");
	else if (tokens->cmd->str[0] == '.' && access(tokens->cmd->str, X_OK) < 0)
		ret = print_cmd_error(tokens->cmd->str, ": Permission denied\n");
	return (ret);
}

/**
 *
 * @brief Main execution function that executes a given token list
 *
 * @param tokens List of tokens to be executed
 * @param env List of environmental variables
 * @return Return value of the command executed, 1 if an error occurred
 */
int	execute(t_token *tokens, t_env **env)
{
	int			ret;
	int			pid;

	ret = init_check(tokens);
	if (ret)
		return (ret);
	if (tokens->next)
		ret = exec_pipe(tokens, env);
	else
	{
		pid = 0;
		ret = dispatch(tokens, env, &pid);
		if (pid)
		{
			close_fds(tokens);
			sig_exec();
			waitpid(pid, &ret, 0);
			ret = WEXITSTATUS(ret);
		}
		free_tokens(tokens);
	}
	sig_inter();
	return (ret);
}
