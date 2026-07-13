/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/13 13:20:58 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *
 * @brief Sends the program to the associated function to execute the command
 *
 * @param token List of tokens to be executed
 * @param env List of environmental variables
 * @param pids Pid list to eventually fill
 * @param is_piped 1 if the command is part of a pipe, else 0
 * @return Return value of the function executed
 */
int	dispatch(t_token *token, t_env **env, t_pid_list *pids, int is_piped)
{
	int		ret;
	t_pid_list	*last;

	ret = check_tkn(token);
	last = get_last_pid(pids);
	if (ret)
		return (ret);
	if (!ft_strncmp(token->cmd->str, "cd", 3))
		ret = exec_cd(token->cmd->next, token->outfile, *env, is_piped);
	else if (!ft_strncmp(token->cmd->str, "export", 7))
		ret = exec_export(token->cmd->next, token->outfile, env, is_piped);
	else if (!ft_strncmp(token->cmd->str, "pwd", 4))
		ret = exec_pwd(token->outfile, *env);
	else if (!ft_strncmp(token->cmd->str, "env", 4))
		ret = exec_env(token->outfile, *env);
	else if (!ft_strncmp(token->cmd->str, "echo", 5))
		ret = exec_echo(token->cmd->next, token->outfile);
	else if (!ft_strncmp(token->cmd->str, "unset", 6))
		ret = exec_unset(token->cmd->next, env, is_piped);
	else if (!ft_strncmp(token->cmd->str, "exit", 5))
		ret = exec_exit(token, *env, is_piped);
	else
		last->pid = exec_child(token, *env, pids);
	return (ret);
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
	if (!tokens || !tokens->cmd || !tokens->cmd->str)
		return (1);
	if (tokens->infile == -1)
		tokens->infile = STDIN_FILENO;
	while (tokens->next)
		tokens = tokens->next;
	if (tokens->outfile == -1)
		tokens->outfile = STDOUT_FILENO;
	return (0);
}

static int	exec_no_pipe(t_token *tokens, t_env **env)
{
	t_pid_list	*child_pid;
	int			ret;

	child_pid = ft_calloc(1, sizeof(t_pid_list));
	if (!child_pid)
		return (1);
	ret = dispatch(tokens, env, child_pid, 0);
	if (child_pid->pid)
	{
		close_fds(tokens);
		sig_exec();
		waitpid(child_pid->pid, &ret, 0);
		ret = WEXITSTATUS(ret);
	}
	free(child_pid);
	free_tokens(tokens);
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

	ret = init_check(tokens);
	if (ret)
		return (ret);
	if (tokens->next)
		ret = exec_pipe(tokens, env);
	else
		ret = exec_no_pipe(tokens, env);
	sig_inter();
	return (ret);
}
