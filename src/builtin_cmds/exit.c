/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:37:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/30 12:56:39 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		free_env_tokens(env, token);
		exit(2);
	}
	if (token->cmd->next->next)
	{
		write(2, "goth_in_the_shell: exit: too many arguments\n", 44);
		return (1);
	}
	code = ft_atoi(token->cmd->next->str);
	free_env_tokens(env, token);
	exit(code % 256);
}
