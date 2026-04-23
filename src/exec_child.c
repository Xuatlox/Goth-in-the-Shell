/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:28:00 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/22 17:18:39 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static char	*valid_cmd(t_command *cmd, t_env *env)
{
	int		i;
	char	*ret;
	char	**paths;
	char	**paths_var;
	char	*absolute_cmd;

	if (*(cmd->str) == '/')
		return (cmd->str);
	paths_var = get_env(env, "PATH");
	paths = ft_split(*paths_var, ':');
	i = 0;
	ret = NULL;
	while (paths && paths[i])
	{
		*paths_var = ft_strjoin(paths[i], "/");
		absolute_cmd = ft_strjoin(*paths_var, cmd->str);
		free(*paths_var);
		if (access(absolute_cmd, X_OK))
			ret = absolute_cmd;
		free(absolute_cmd);
		free(paths[i]);
		++i;
	}
	free(paths);
	return (ret);
}

static char	**fill_argv(const t_command *cmd)
{
	char	**argv;
	int		i;
	int		size;

	size = get_cmd_size(cmd);
	argv = ft_calloc(size, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (cmd)
	{
		argv[i] = ft_strdup(cmd->str);
		cmd = cmd->next;
		++i;
	}
	return (argv);
}

static char	**fill_envp(const t_env *env)
{
	char	**envp;
	int		i;
	int		size;
	char	*tmp;

	size = get_env_size(env);
	envp = ft_calloc(size, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		envp[i] = ft_strjoin(tmp, env->val);
		free(tmp);
		++i;
		env = env->next;
	}
	return (envp);
}

static void	free_all(char **envp, char **argv)
{
	int	i;

	if (envp)
	{
		i = 0;
		while (envp[i])
		{
			free(envp[i]);
			++i;
		}
		free(envp);
	}
	if (argv)
	{
		i = 0;
		while (argv[i])
		{
			free(argv[i]);
			++i;
		}
		free(argv);
	}
}

int	exec_child(t_command *cmd, const int fd_in, const int fd_out, t_env *env)
{
	pid_t	pid;
	char	*absolute_cmd;
	char	**envp;
	char	**argv;

	if (!cmd)
		return (0);
	absolute_cmd = valid_cmd(cmd, env);
	argv = fill_argv(cmd);
	envp = fill_envp(env);
	if (!absolute_cmd)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0
				|| dup2(fd_out, STDOUT_FILENO) < 0)
			exit(0);
		execve(absolute_cmd, argv, envp);
	}
	free_all(envp, argv);
	return (1);
}
