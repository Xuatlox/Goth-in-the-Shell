/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/02 11:05:08 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the name given is valid and gives its length in this case
 *
 * @param str Argument given after the 'export' command
 * @return The size of the given variable name, or 0 if not valid
 */
static int	is_valid_id(char *str)
{
	int		i;

	if (!*str || (*str >= '0' && *str <= '9') || *str == '=')
	{
		print_error_export(str);
		return (0);
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= '0' && str[i] <= '9')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= 'a' && str[i] <= 'z') && str[i] != '_')
		{
			print_error_export(str);
			return (0);
		}
		++i;
	}
	return (i);
}

/**
 * @brief Allocates the new variable to be exported
 *
 * @param str Argument given after the 'export' command
 * @param name Pointer to the name of the variable to be exported
 * @param val Pointer to the value of the variable to be exported
 * @return 0 on success, 1 if an error occurred
 */
static int	alloc_var(char *str, char **name, char **val)
{
	char	*tmp;
	int		name_size;

	*val = NULL;
	name_size = is_valid_id(str);
	if (!name_size)
		return (1);
	*name = ft_calloc(name_size + 1, sizeof(char));
	if (!*name)
	{
		perror("goth_in_the_shell: export");
		return (1);
	}
	tmp = ft_strchr(str, '=');
	if (tmp)
	{
		*val = ft_strdup(tmp + 1);
		if (!*val)
		{
			free(*name);
			perror("goth_in_the_shell: export");
			return (1);
		}
	}
	return (0);
}

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
static void	print_sorted_env(t_env *env, const int fd_out)
{
	t_env	*var;
	char	*last;
	size_t	size;

	last = "";
	var = find_next_var(env, last);
	while (var)
	{
		last = var->name;
		write(fd_out, "declare -x ", 11);
		size = ft_strlen(last);
		write(fd_out, last, size);
		write(fd_out, "=\"", 2);
		if (var->val)
		{
			size = ft_strlen(var->val);
			write(fd_out, var->val, size);
		}
		write(fd_out, "\"\n", 2);
		var = find_next_var(env, last);
	}
}

/**
 * @brief Mimics the behavior of the export command in bash
 *
 * @param args Argument list following the 'export' command
 * @param fd_out Fd where the output must be sent
 * @param env List of environmental variables
 * @return 0 on success, 1 if an error occurred
 */
int	exec_export(const t_command *args, const int fd_out, t_env **env)
{
	char	*name;
	char	*val;
	int		i;

	if (!args)
		print_sorted_env(*env, fd_out);
	while (args)
	{
		if (alloc_var(args->str, &name, &val))
			return (1);
		i = 0;
		while (args->str[i] && args->str[i] != '=')
		{
			name[i] = args->str[i];
			++i;
		}
		if (*env && !add_env(*env, name, val))
			return (1);
		if (!*env)
			*env = new_env(name, val);
		if (!*env)
			return (1);
		args = args->next;
	}
	return (0);
}
