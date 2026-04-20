/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:37:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/20 18:00:26 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void	free_all(t_env *env, t_command *cmd)
{
	t_env		*tmp_env;
	t_command	*tmp_cmd;

	while (env)
	{
		tmp_env = env->next;
		free(env->name);
		free(env->val);
		free(env);
		env = tmp_env;
	}
	while (cmd)
	{
		tmp_cmd = cmd->next;
		free(cmd->str);
		free(cmd);
		cmd = tmp_cmd;
	}
}

int	exec_exit(t_command *args, t_env *env)
{
	write(STDOUT_FILENO, "exit\n", 5);
	free_all(env, args);
	return (1);
}
