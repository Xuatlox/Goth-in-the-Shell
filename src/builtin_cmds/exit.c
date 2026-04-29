/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:37:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/29 14:56:37 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_all(t_env *env, t_token *token)
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
	while (token->cmd)
	{
		tmp_cmd = token->cmd->next;
		free(token->cmd->str);
		free(token->cmd);
		token->cmd = tmp_cmd;
	}
	free(token);
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

int	exec_exit(t_token *token, t_env *env)
{
	int	code;
	int	size;

	write(1, "exit\n", 5);
	if (!token->cmd->next || !is_num(token->cmd->next->str))
	{
		size = ft_strlen(token->cmd->next->str);
		write(2, "goth_in_the_shell: exit: ", 25);
		write(2, token->cmd->next->str, size);
		write(2, "\n", 1);
		free_all(env, token);
		exit(2);
	}
	if (token->cmd->next->next)
	{
		write(2, "goth_in_the_shell: exit: too many arguments\n", 44);
		return (-1);
	}
	code = ft_atoi(token->cmd->next->str);
	free_all(env, token);
	exit(code % 256);
}
