/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:13:51 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/17 10:46:09 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the last error encountered
 *
 * @param dest Argument given after the 'cd' in the command line
 */
static void	print_cd_error(char *dest)
{
	write(2, "goth_in_the_shell: cd: ", 23);
	perror(dest);
}

/**
 * @brief Sets dest to HOME
 *
 * @param env List of environmental variables
 * @param dest Pointer to the string containing the destination of the command
 * @return 0 on success, 1 if an error occurred
 */
static int	cd_home(t_env *env, char **dest)
{
	char	**home;

	home = get_env(env, "HOME");
	if (home)
	{
		*dest = *home;
		return (0);
	}
	write(STDERR_FILENO, "goth_in_the_shell: cd: HOME not set\n", 36);
	return (1);
}

/**
 * @brief Operates the directory change using getcwd() and updates env PWD and
 * OLDPWD
 *
 * @param dest Pointer to the string containing the destination of the command
 * @param env List of environmental variables

 * @return 0 on success, 1 if an error occurred
 */
static int	change_directory(char *dest, t_env *env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		print_cd_error(dest);
		return (1);
	}
	if (chdir(dest))
	{
		print_cd_error(dest);
		free(path);
		return (1);
	}
	set_env("OLDPWD", path, env);
	path = getcwd(NULL, 0);
	if (!path)
	{
		print_cd_error(dest);
		return (1);
	}
	set_env("PWD", path, env);
	return (0);
}

/**
 * @brief Mimics the behavior of the cd command in bash
 *
 * @param args List of arguments following 'cd' (NULL if no arguments)
 * @param fd_out Fd where the output must be sent
 * @param env List of environmental variables
 * @param is_piped Indicates if the command is in a pipe (1) or not (0)
 * @return 0 on success, 1 if an error occurred
 */
int	exec_cd(const t_command *args, t_env *env, int is_piped)
{
	char	*dest;
	int		ret;

	if (args)
		dest = args->str;
	if (!args && !cd_home(env, &dest))
		return (1);
	ret = 0;
	if (!is_piped)
		ret = change_directory(dest, env);
	return (ret);
}
