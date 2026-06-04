/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/04 13:10:25 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Displays an error message if an 'export' argument is incorrect
 *
 * @param str Argument given after the 'export' command
 */
static void	print_error_export(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	write(2, "goth_in_the_shell: export: `", 28);
	write(2, str, size);
	write(2, "': not a valid identifier\n", 26);
}

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
 * @return 0 on success, 1 if an error occurred, 2 if the id is invalid
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
 * @brief Fills the "name" variable from the second argument given in "args"
 *
 * @param name Pointer to the string to fill with the name of the variable
 * @param args List of arguments given after "export" command
 */
static void	fill_name(char **name, const t_command *args)
{
	int	i;

	i = 0;
	while (args->str[i] && args->str[i] != '=')
	{
		(*name)[i] = args->str[i];
		++i;
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
	int		ret;

	if (!args)
		print_sorted_env(*env, fd_out);
	ret = 0;
	while (args && args->str)
	{
		if (!alloc_var(args->str, &name, &val))
		{
			fill_name(&name, args);
			if (*env && add_env(*env, name, val))
				return (1);
			if (!*env)
				*env = new_env(name, val);
			if (!*env)
				return (1);
		}
		else
			ret = 1;
		args = args->next;
	}
	return (ret);
}
