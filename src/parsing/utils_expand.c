/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:17:53 by mcrenn            #+#    #+#             */
/*   Updated: 2026/06/01 09:40:11 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_strlen_bash(char *str)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
	else if (str[0] == '?' || str[0] == '@' || str[0] == '*' || str[0] == '#'
		|| str[0] == '$' || str[0] == '!' || str[0] == '-' || str[0] == '_'
		|| ft_isdigit(str[0]))
		i = 1;
	return (i);
}

char	*make_env_var(char *str)
{
	int		wlen;
	char	*env_var;

	wlen = ft_strlen_bash(str);
	env_var = ft_calloc(wlen + 1, 1);
	if (!env_var)
		return (NULL);
	ft_strlcpy(env_var, str, wlen + 1);
	return (env_var);
}

char	*fill_error_code(t_minishell *minishell)
{
	char	*error_code;

	error_code = ft_itoa(minishell->old_error_code);
	if (!error_code)
		return (NULL);
	return (error_code);
}

char	*make_env_val(t_minishell *minishell, char *env_var)
{
	char	*error_code;
	t_env	*env;

	if (!minishell->env)
		return (NULL);
	env = minishell->env;
	while (env)
	{
		if (ft_strcmp(env_var, env->name) == 0)
		{
			error_code = ft_strdup(env->val);
			if (!error_code)
				return (NULL);
			return (error_code);
		}
		env = env->next;
	}
	if (ft_strcmp(env_var, "?") == 0)
	{
		error_code = fill_error_code(minishell);
		return (error_code);
	}
	return (NULL);
}
