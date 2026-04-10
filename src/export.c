/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:06:27 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/10 15:26:46 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static int	check_var_name(const char *str, char **name, char **val)
{
	int	i;

	if (*str >= '0' && *str <= '9')
	{
		perror("not a valid identifier");
		return (0);
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= '0' && str[i] <= '9')
				&& !(str[i] >= 'A' && str[i] <= 'Z')
				&& !(str[i] >= 'a' && str[i] <= 'z') && str[i] != '_')
			return (0);
		++i;
	}
	if (str[i] == '=')
		*val = ft_strdup(&str[i + 1]);
	else
		*val = NULL;
	*name = ft_calloc(i + 1, sizeof(char));
	return (1);
}

static t_env	*find_next_var(t_env *env, const char *last)
{
	t_env	*var;
	int		last_index;
	int		var_index;

	var = NULL;
	while (env)
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

static void	print_sorted_env(t_env *env, const int fd_out)
{
	t_env	*var;
	char	*last;
	int		size;

	last = "";
	var = find_next_var(env, last);
	while (var)
	{
		last = var->name;
		write(fd_out, "declare -x ", 11);
		size = ft_strlen(last);
		write(fd_out, last, size);
		write(fd_out, "=\"", 2);
		size = ft_strlen(var->val);
		write(fd_out, var->val, size);
		write(fd_out, "\"\n", 2);
		var = find_next_var(env, last);
	}
}

static void	add_env(t_env *env, char *name, char *value)
{
	char	**get;
	t_env	*new;

	get = get_env(env, name);
	if (get)
	{
		if (*get)
			free(*get);
		*get = value;
	}
	else
	{
		new = malloc(sizeof(t_env));
		new->name = name;
		new->val = value;
		new->next = NULL;
		while (env->next)
			env = env->next;
		env->next = new;
	}
}

int	exec_export(const t_command *args, const int fd_out, t_env *env)
{
	char	*name;
	char	*val;
	int		i;

	if (!args)
	{
		print_sorted_env(env, fd_out);
		return (1);
	}
	if (!check_var_name(args->str, &name, &val))
		return (0);
	i = 0;
	while (args->str[i] && args->str[i] != '=')
	{
		name[i] = args->str[i];
		++i;
	}
	add_env(env, name, val);
	return (1);
}
