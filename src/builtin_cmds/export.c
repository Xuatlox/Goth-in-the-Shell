/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:45:19 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/13 13:34:13 by ansimonn         ###   ########.fr       */
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

	if (!*str || (*str >= '0' && *str <= '9') || *str == '='
		|| (*str == '+' && *(str + 1) == '='))
	{
		print_error_export(str);
		return (0);
	}
	i = 0;
	while (str[i] && !(str[i] == '=' || (str[i] == '+' && str[i + 1] == '=')))
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
 * @brief Creates the name of the new variable to be exported
 *
 * @param str User given input
 * @param name Pointer to the name of the variable to be exported
 * @param size Name size
 * @return 0 on success, 1 if an error occurred
 */
static int	create_name(char *str, char **name, int size)
{
	int		i;

	if (!size)
		return (1);
	*name = ft_calloc(size + 1, sizeof(char));
	if (!*name)
	{
		perror("goth_in_the_shell: export");
		return (1);
	}
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		(*name)[i] = str[i];
		++i;
	}
	return (0);
}

/**
 * @brief Creates the value of the new variable to be exported
 *
 * @param name Pointer to the name of the variable to be exported
 * @param val Pointer to the value of the variable to be exported
 * @param str User given input
 * @param env List of environmental variables
 * @return 0 on success, 1 if an error occurred
 */
static int	create_val(char *name, char **val, char *str, t_env *env)
{
	char	*tmp;
	char	**old;

	*val = NULL;
	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (0);
	if (*(tmp - 1) == '+')
	{
		old = get_env(env, name);
		if (old)
			*val = ft_strjoin(*old, tmp + 1);
	}
	if (!*val)
		*val = ft_strdup(tmp + 1);
	if (!*val)
	{
		free(name);
		perror("goth_in_the_shell: export");
		return (1);
	}
	return (0);
}

/**
 * @brief Mimics the behavior of the export command in bash
 *
 * @param args Argument list following the 'export' command
 * @param fd_out Fd where the output must be sent
 * @param env List of environmental variables
 * @param is_piped Indicates if the command is in a pipe (1) or not (0)
 * @return 0 on success, 1 if an error occurred
 */
int	exec_export(t_command *args, int fd_out, t_env **env, int is_piped)
{
	char	*name;
	char	*val;
	int		ret;
	int		size;

	if (!args)
		print_sorted_env(*env, fd_out);
	ret = 0;
	while (args && args->str)
	{
		size = is_valid_id(args->str);
		if (!is_piped)
		{
			if (!create_name(args->str, &name, size)
				&& !create_val(name, &val, args->str, *env))
			{
				if (add_env(env, name, val))
					return (1);
			}
			else
				ret = 1;
		}
		args = args->next;
	}
	return (ret);
}
