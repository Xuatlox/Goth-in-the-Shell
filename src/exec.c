/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/30 12:53:13 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

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
		ret = exec_env(token->cmd->next, token->outfile, env);
	else if (!ft_strncmp(token->cmd->str, "echo", 5))
		ret = exec_echo(token->cmd->next, token->outfile);
	else if (!ft_strncmp(token->cmd->str, "unset", 6))
		ret = exec_unset(token->cmd->next, env);
	else if (!ft_strncmp(token->cmd->str, "exit", 5))
		ret = exec_exit(token, env);
	else
		ret = exec_child(token, env);
	return (ret);
}

int	execute(t_token *tokens, t_env *env)
{
	t_command	*tmp;
	int			ret;

	if (!tokens || !env)
		return (EXIT_FAILURE);
	if (tokens->next)
		ret = exec_pipe(tokens, env);
	else
		ret = dispatch(tokens, env);
	while (tokens)
	{
		close(tokens->infile);
		close(tokens->outfile);
		while (tokens->cmd)
		{
			tmp = tokens->cmd->next;
			free(tokens->cmd->str);
			free(tokens->cmd);
			tokens->cmd = tmp;
		}
		tokens = tokens->next;
	}
	return (ret);
}
