/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/18 13:36:24 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dispatch(t_token *token, t_env *env)
{
	int	ret;

	if (!ft_strncmp(token->cmd->str, "cd", 3))
		ret = exec_cd(token->cmd->next, token->outfile, env);
	else if (!ft_strncmp(token->cmd->str, "export", 7))
		ret = exec_export(token->cmd->next, token->outfile, env);
	else if (!ft_strncmp(token->cmd->str, "pwd", 4))
		ret = exec_pwd(token->outfile, env);
	else if (!ft_strncmp(token->cmd->str, "env", 4))
		ret = exec_env(token->outfile, env);
	else if (!ft_strncmp(token->cmd->str, "echo", 5))
		ret = exec_echo(token->cmd->next, token->outfile);
	else if (!ft_strncmp(token->cmd->str, "unset", 6))
		ret = exec_unset(token->cmd->next, env);
	else if (!ft_strncmp(token->cmd->str, "exit", 5))
		ret = exec_exit(token, env);
	else
		ret = exec_child(token, env);
	free_tokens(token);
	return (ret);
}

static void	set_outfile(t_token *tokens)
{
	tokens->infile = STDIN_FILENO;
	while (tokens->next)
		tokens = tokens->next;
	tokens->outfile = STDOUT_FILENO;
}

int	execute(t_token *tokens, t_env *env)
{
	int			ret;

	if (!tokens || !tokens->cmd || !tokens->cmd->str)
		return (1);
	set_outfile(tokens);
	if (tokens->next)
		ret = exec_pipe(tokens, env);
	else
		ret = dispatch(tokens, env);
	return (ret);
}
