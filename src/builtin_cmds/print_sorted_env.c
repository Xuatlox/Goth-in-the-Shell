/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:59:11 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/04 13:21:58 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Search through the env for the next variable following 'last' in
 * alphanumeric order
 *
 * @param env List of environmental variables
 * @param last Last variable returned
 * @return Next variable found
 */
static t_env	*find_next_var(t_env *env, const char *last)
{
	t_env	*var;
	int		last_index;
	int		var_index;

	var = NULL;
	while (env && last)
	{
		last_index = 0;
		var_index = 0;
		while (last[last_index] && env->name[last_index]
			&& env->name[last_index] == last[last_index])
			++last_index;
		while (var && var->name[var_index] && env->name[var_index]
			&& env->name[var_index] == var->name[var_index])
			++var_index;
		if (env->name[last_index] > last[last_index]
			&& (!var || env->name[var_index] < var->name[var_index]))
			var = env;
		env = env->next;
	}
	return (var);
}

/**
 * @brief Prints all env variables following the alphanumerical order
 *
 * @param env List of environmental variables
 * @param fd_out Fd where the output must be sent
 */
void	print_sorted_env(t_env *env, const int fd_out)
{
	t_env	*var;
	char	*last;
	size_t	size;

	last = "";
	var = find_next_var(env, last);
	while (var)
	{
		last = var->name;
		write(fd_out, "export ", 7);
		size = ft_strlen(last);
		write(fd_out, last, size);
		if (var->val)
		{
			write(fd_out, "=\"", 2);
			size = ft_strlen(var->val);
			write(fd_out, var->val, size);
			write(fd_out, "\"", 1);
		}
		write(fd_out, "\n", 1);
		var = find_next_var(env, last);
	}
}
