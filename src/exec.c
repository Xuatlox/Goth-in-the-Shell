/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/27 15:38:26 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void	dispatch(t_command *cmd, int fd_in, int fd_out, t_env *env)
{
	if (!ft_strncmp(cmd->str, "cd", 3))
		exec_cd(cmd->next, fd_out, env);
	else if (!ft_strncmp(cmd->str, "export", 7))
		exec_export(cmd->next, fd_out, env);
	else if (!ft_strncmp(cmd->str, "pwd", 4))
		exec_pwd(fd_out, env);
	else if (!ft_strncmp(cmd->str, "env", 4))
		exec_env(cmd->next, fd_out, env);
	else if (!ft_strncmp(cmd->str, "echo", 5))
		exec_echo(cmd->next, fd_out);
	else if (!ft_strncmp(cmd->str, "unset", 6))
		exec_unset(cmd->next, env);
	else if (!ft_strncmp(cmd->str, "exit", 5))
		exec_exit(cmd, env);
	else
		exec_child(cmd, fd_in, fd_out, env);
}

void	execute(t_token *tokens, t_env *env)
{
	t_command	*tmp;

	while (tokens)
	{
		dispatch(tokens->cmd, tokens->infile, tokens->outfile, env);
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
}
