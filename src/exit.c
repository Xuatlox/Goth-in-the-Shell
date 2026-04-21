/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:37:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/21 15:08:53 by ansimonn         ###   ########.fr       */
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

static int	is_num(const char *str)
{
	if (!str)
		return (0);
	if (*str == '-' || *str == '+')
		++str;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		++str;
	}
	return (1);
}

int	exec_exit(t_command *cmd, t_env *env)
{
	int	code;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!is_num(cmd->next->str))
	{
		free_all(env, cmd);
		exit(2);
	}
	if (cmd->next->next->str)
		return (0);
	code = ft_atoi(cmd->next->str);
	free_all(env, cmd);
	exit(code % 256);
}
