/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:59:48 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/28 16:57:03 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	clean_child(t_env *env, t_token *token)
{
	t_env		*tmp_env;
	t_command	*tmp_cmd;

	if (token->infile > -1)
		close(token->infile);
	if (token->outfile > -1)
		close(token->outfile);
	while (env)
	{
		tmp_env = env->next;
		free(env->name);
		free(env->val);
		free(env);
		env = tmp_env;
	}
	while (token->cmd)
	{
		tmp_cmd = token->cmd->next;
		free(token->cmd->str);
		free(token->cmd);
		token->cmd = tmp_cmd;
	}
	free(token);
}
