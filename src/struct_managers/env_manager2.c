/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:25:08 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/12 13:30:33 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

t_env	*build_env(char **envp)
{
	char	**sep;
	t_env	*env;
	t_env	*ret;

	env = malloc(sizeof(t_env));
	ft_bzero(env, sizeof(t_env));
	while (*envp)
	{
		sep = ft_split(*envp, '=');
		if (!sep || add_env(env, sep[0], sep[1]))
		{
			free_env(env);
			return (NULL);
		}
		free(sep);
		++envp;
	}
	ret = env->next;
	free(env);
	return (ret);
}
