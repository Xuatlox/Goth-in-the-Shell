/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:13:51 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/13 14:28:51 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cd_old_wd(t_env *env, char **dest, const int fd_out)
{
	char	**path;
	size_t	size;

	path = get_env(env, "OLDPWD");
	if (!path)
	{
		write(STDERR_FILENO, "goth_in_the_shell: cd: OLDPWD not set\n", 38);
		return (1);
	}
	*dest = *path;
	size = ft_strlen(*dest);
	write(fd_out, *dest, size);
	write(fd_out, "\n", 1);
	return (0);
}

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

static int	change_directory(char *dest, t_env *env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("goth_in_the_shell: cd");
		return (1);
	}
	if (chdir(dest))
	{
		perror("goth_in_the_shell: cd");
		free(path);
		return (1);
	}
	set_env("OLDPWD", path, env);
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("goth_in_the_shell: cd");
		return (1);
	}
	set_env("PWD", path, env);
	return (0);
}

int	exec_cd(const t_command *args, const int fd_out, t_env *env)
{
	char	*dest;
	int		ret;

	if (args)
		dest = args->str;
	if (!args && cd_home(env, &dest))
		return (1);
	if (args && !ft_strncmp(args->str, "-", 2)
		&& cd_old_wd(env, &dest, fd_out))
		return (1);
	ret = change_directory(dest, env);
	return (ret);
}
