/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:28:00 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/30 14:06:25 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void	free_all(char **ar1, char **ar2, char *str)
{
	int	i;

	if (str)
		free(str);
	if (ar1)
	{
		i = 0;
		while (ar1[i])
		{
			free(ar1[i]);
			++i;
		}
		free(ar1);
	}
	if (ar2)
	{
		i = 0;
		while (ar2[i])
		{
			free(ar2[i]);
			++i;
		}
		free(ar2);
	}
}

static char	*valid_cmd(t_command *cmd, t_env *env)
{
	int		i;
	char	*ret;
	char	**paths;
	char	*paths_var;
	char	*absolute_cmd;

	if (*(cmd->str) == '/')
		return (cmd->str);
	paths_var = *get_env(env, "PATH");
	paths = ft_split(paths_var, ':');
	i = 0;
	ret = NULL;
	while (paths && paths[i])
	{
		paths_var = ft_strjoin(paths[i], "/");
		absolute_cmd = ft_strjoin(paths_var, cmd->str);
		free(paths_var);
		if (!ret && access(absolute_cmd, X_OK))
			ret = ft_strdup(absolute_cmd);
		free(absolute_cmd);
		++i;
	}
	free_all(paths, NULL, NULL);
	return (ret);
}

static char	**fill_argv(const t_command *cmd)
{
	char	**argv;
	int		i;
	int		size;

	size = get_cmd_size(cmd);
	argv = ft_calloc(size + 1, sizeof(char *));
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
	envp = ft_calloc(size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		if (!tmp)
		{
			free_all(envp, NULL, NULL);
			return (NULL);
		}
		envp[i] = ft_strjoin(tmp, env->val);
		if (!envp[i])
		{
			free_all(envp, NULL, tmp);
			return (NULL);
		}
		free(tmp);
		++i;
		env = env->next;
	}
	return (envp);
}

int	exec_child(t_token *token, t_env *env)
{
	pid_t	pid;
	char	*absolute_cmd;
	char	**envp;
	char	**argv;
	int		exit_code;

	if (!token || !token->cmd)
		return (1);
	absolute_cmd = valid_cmd(token->cmd, env);
	argv = fill_argv(token->cmd);
	envp = fill_envp(env);
	if (!absolute_cmd || !envp || !argv)
	{
		free_all(envp, argv, absolute_cmd);
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (dup2(token->infile, STDIN_FILENO) < 0
				|| dup2(token->outfile, STDOUT_FILENO) < 0)
			exit(0);
		clean_child(env, token);
		execve(absolute_cmd, argv, envp);
		free_all(envp, argv, absolute_cmd);
		exit(0);
	}
	waitpid(pid, &exit_code, 0);
	free_all(envp, argv, absolute_cmd);
	return (exit_code);
}
