/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/27 18:27:22 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	set_outfile(t_token *tokens)
{
	if (tokens->infile == -1)
		tokens->infile = STDIN_FILENO;
	while (tokens->next)
		tokens = tokens->next;
	if (tokens->outfile == -1)
		tokens->outfile = STDOUT_FILENO;
}

static int	check_cmd(t_token *tokens)
{
	size_t	size;

	if (!tokens || !tokens->cmd || !tokens->cmd->str)
		return (1);
	if (*tokens->cmd->str == '/' || !ft_strncmp(tokens->cmd->str, ".", 2))
	{
		write(2, "goth_in_the_shell: ", 19);
		size = ft_strlen(tokens->cmd->str);
		write(2, tokens->cmd->str, size);
		if (*tokens->cmd->str == '/')
			write(2, ": Is a directory\n", 17);
		else
			write(2, ": filename argument required\n", 29);
		return (1);
	}
	return (0);
}

int	execute(t_token *tokens, t_env **env)
{
	int			ret;
	int			pid;

	if (check_cmd(tokens))
		return (1);
	set_outfile(tokens);
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
