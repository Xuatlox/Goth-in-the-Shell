/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/17 10:23:56 by mcrenn           ###   ########.fr       */
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
 * @param is_pipe 1 if the command is part of a pipe, else 0
 * @return Return value of the function executed
 */
int	dispatch(t_token **token, t_env **env, t_pid_list *pids, int is_pipe)
{
	int			ret;
	t_pid_list	*last;

	ret = check_tkn(*token);
	last = get_last_pid(pids);
	if (ret)
		return (ret);
	if ((*token)->cmd && !ft_strncmp((*token)->cmd->str, "cd", 3))
		ret = exec_cd((*token)->cmd->next, *env, is_pipe);
	else if ((*token)->cmd && !ft_strncmp((*token)->cmd->str, "export", 7))
		ret = exec_export((*token)->cmd->next, (*token)->outfile, env, is_pipe);
	else if ((*token)->cmd && !ft_strncmp((*token)->cmd->str, "pwd", 4))
		ret = exec_pwd((*token)->outfile, *env);
	else if ((*token)->cmd && !ft_strncmp((*token)->cmd->str, "env", 4))
		ret = exec_env((*token)->outfile, *env);
	else if ((*token)->cmd && !ft_strncmp((*token)->cmd->str, "echo", 5))
		ret = exec_echo((*token)->cmd->next, (*token)->outfile);
	else if ((*token)->cmd && !ft_strncmp((*token)->cmd->str, "unset", 6))
		ret = exec_unset((*token)->cmd->next, env, is_pipe);
	else if ((*token)->cmd && !ft_strncmp((*token)->cmd->str, "exit", 5))
		ret = exec_exit(token, *env, is_pipe, pids);
	else if ((*token)->cmd)
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
	if ((!tokens || !tokens->cmd || !tokens->cmd->str) && tokens->infile == -1
		&& tokens->outfile == -1 && tokens->is_fail == SUCCESS)
		return (1);
	if (tokens->infile == -1)
		tokens->infile = STDIN_FILENO;
	while (tokens->next)
		tokens = tokens->next;
	if (tokens->outfile == -1)
		tokens->outfile = STDOUT_FILENO;
	return (0);
}

static int	exec_no_pipe(t_token **tokens, t_env **env)
{
	t_pid_list	*child_pid;
	int			ret;
	int			status;

	child_pid = ft_calloc(1, sizeof(t_pid_list));
	if (!child_pid)
		return (1);
	status = dispatch(tokens, env, child_pid, 0);
	if (child_pid->pid)
	{
		close_fds(*tokens);
		sig_exec();
		waitpid(child_pid->pid, &ret, 0);
		if (WIFEXITED(ret))
			status = WEXITSTATUS(ret);
		if (WIFSIGNALED(ret))
			status = WTERMSIG(ret) + 128;
	}
	free(child_pid);
	close_fds(*tokens);
	free_tokens(tokens);
	return (status);
}

/**
 *
 * @brief Main execution function that executes a given token list
 *
 * @param tokens List of tokens to be executed
 * @param env List of environmental variables
 * @return Return value of the command executed, 1 if an error occurred
 */
int	execute(t_token **tokens, t_env **env)
{
	int			ret;

	ret = init_check(*tokens);
	if (ret)
		return (0);
	if ((*tokens)->next)
		ret = exec_pipe(tokens, env);
	else
		ret = exec_no_pipe(tokens, env);
	sig_inter();
	return (ret);
}
