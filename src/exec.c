/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/28 16:57:38 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static int	dispatch(t_command *cmd, int fd_out, t_env *env)
{
	int	ret;

	if (!ft_strncmp(cmd->str, "cd", 3))
		ret = exec_cd(cmd->next, fd_out, env);
	else if (!ft_strncmp(cmd->str, "export", 7))
		ret = exec_export(cmd->next, fd_out, env);
	else if (!ft_strncmp(cmd->str, "pwd", 4))
		ret = exec_pwd(fd_out, env);
	else if (!ft_strncmp(cmd->str, "env", 4))
		ret = exec_env(cmd->next, fd_out, env);
	else if (!ft_strncmp(cmd->str, "echo", 5))
		ret = exec_echo(cmd->next, fd_out);
	else if (!ft_strncmp(cmd->str, "unset", 6))
		ret = exec_unset(cmd->next, env);
	else if (!ft_strncmp(cmd->str, "exit", 5))
		ret = exec_exit(cmd, env);
	else
		return (-1);
	return (ret);
}

void	execute(t_token *tokens, t_env *env)
{
	t_command	*tmp;

	if (!tokens || !env)
		return ;
	if (tokens->next)
		exec_pipe(tokens, env);
	else if (dispatch(tokens->cmd, tokens->outfile, env) == -1)
	{
		exec_child(tokens, env);
	}
	close(tokens->infile);
	close(tokens->outfile);
	while (tokens->cmd)
	{
		tmp = tokens->cmd->next;
		free(tokens->cmd->str);
		free(tokens->cmd);
		tokens->cmd = tmp;
	}
}
