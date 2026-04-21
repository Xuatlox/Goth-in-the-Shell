/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:28:00 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/21 16:26:12 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static int	valid_cmd(t_command *cmd, t_env *env)
{
	int		i;
	int		ret;
	char	**paths;
	char	**paths_var;
	char	*absolute_cmd;

	paths_var = get_env(env, "PATH");
	paths = ft_split(*paths_var, ':');
	i = 0;
	ret = 0;
	while (paths && paths[i])
	{
		absolute_cmd = ft_strjoin(paths[i], cmd->str);
		if (access(absolute_cmd, X_OK))
			ret = 1;
		free(absolute_cmd);
		free(paths[i]);
		++i;
	}
	free(paths);
	return (ret);
}

int	exec_child(t_command *cmd, int fd_in, int fd_out, t_env *env)
{
	pid_t	pid;

	if (!valid_cmd(cmd, env))
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0
				|| dup2(fd_out, STDOUT_FILENO) < 0)
			exit(0);
		execve();
	}
}
