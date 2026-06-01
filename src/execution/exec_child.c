/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:28:00 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/29 11:00:23 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *
 * @brief Searches a valid path for the command
 *
 * @param cmd List of arguments of the command
 * @param env List of environmental variables
 * @param exec Structure containing every data needed to execute execve()
 */
static void	fill_valid_cmd(char *cmd, t_env *env, t_exec *exec)
{
	int		i;
	char	**paths;
	char	**paths_var;
	char	*cmd_tmp;
	char	*tmp;

	paths_var = get_env(env, "PATH");
	if (!paths_var)
		return ;
	paths = ft_split(*paths_var, ':');
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_tmp = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!exec->absolute_cmd && access(cmd_tmp, X_OK) == 0)
			exec->absolute_cmd = ft_strdup(cmd_tmp);
		free(cmd_tmp);
		++i;
	}
	if (!exec->absolute_cmd)
		exec->absolute_cmd = ft_strdup(cmd);
	free_ar(paths);
}

/**
 *
 * @brief Creates a char **args and stores it in the exec structure
 *
 * @param cmd List of arguments of the command
 * @param exec Structure containing every data needed to execute execve()
 */
static void	fill_args(const t_command *cmd, t_exec *exec)
{
	int		i;
	int		size;

	size = cmd_len(cmd);
	exec->args = ft_calloc(size + 1, sizeof(char *));
	if (!exec->args)
		return ;
	i = 0;
	while (cmd)
	{
		exec->args[i] = ft_strdup(cmd->str);
		if (!exec->args[i])
			free_ar(exec->args);
		cmd = cmd->next;
		++i;
	}
}

/**
 *
 * @brief Creates a char **env and stores it in the exec structure
 *
 * @param env List of environmental variables
 * @param exec Structure containing every data needed to execute execve()
 */
static void	fill_env(const t_env *env, t_exec *exec)
{
	int		i;
	int		size;
	char	*tmp;

	size = get_env_size(env);
	exec->env = ft_calloc(size + 1, sizeof(char *));
	if (!exec->env)
		return ;
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		exec->env[i] = ft_strjoin(tmp, env->val);
		if (!exec->env[i])
		{
			free_ar(exec->env);
			free(tmp);
			return ;
		}
		free(tmp);
		++i;
		env = env->next;
	}
}

/**
 *
 * @brief Executes a command that is non-builtin
 *
 * @param token List of tokens to be executed
 * @param env List of environmental variables
 * @return Pid of the new children created
 */
pid_t	exec_child(t_token *token, t_env *env)
{
	t_exec	*exec;
	pid_t	pid;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (1);
	fill_valid_cmd(token->cmd->str, env, exec);
	fill_args(token->cmd, exec);
	fill_env(env, exec);
	if (!exec->absolute_cmd || !exec->env || !exec->args)
	{
		free_exec(exec);
		return (1);
	}
	pid = manage_child(env, token, exec);
	return (pid);
}
