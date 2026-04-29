/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:13:51 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/29 18:10:03 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cd_old_wd(t_env *env, char **dest, const int fd_out)
{
	char	**path;
	int		size;

	path = get_env(env, "OLDPWD");
	if (path)
		*dest = *path;
	size = ft_strlen(*dest);
	write(fd_out, *dest, size);
	write(fd_out, "\n", 1);
}

static int	cd_home(t_env *env, char **dest)
{
	char	**home;

	home = get_env(env, "HOME");
	if (home)
	{
		*dest = *home;
		return (1);
	}
	write(2, "goth_in_the_shell: cd: HOME not set\n", 36);
	return (0);
}

int	exec_cd(const t_command *args, const int fd_out, t_env *env)
{
	char	*path;
	char	*dest;

	if (!args && !cd_home(env, &dest))
		return (0);
	if (!ft_strncmp(args->str, "-", 2))
		cd_old_wd(env, &dest, fd_out);
	else
		dest = args->str;
	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	if (chdir(dest))
	{
		free(path);
		return (0);
	}
	set_env("OLDPWD", path, env);
	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	set_env("PWD", path, env);
	return (1);
}
