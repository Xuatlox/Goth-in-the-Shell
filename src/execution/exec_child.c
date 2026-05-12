/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:28:00 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/07 14:16:16 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	fill_valid_cmd(const t_command *cmd, t_env *env, t_exec *exec)
{
	int		i;
	char	**paths;
	char	*paths_var;
	char	*cmd_tmp;

	if (*cmd->str == '/' && access(cmd->str, X_OK) == 0)
	{
		exec->absolute_cmd = cmd->str;
		return ;
	}
	paths_var = *get_env(env, "PATH");
	paths = ft_split(paths_var, ':');
	i = 0;
	exec->absolute_cmd = NULL;
	while (paths && paths[i])
	{
		paths_var = ft_strjoin(paths[i], "/");
		cmd_tmp = ft_strjoin(paths_var, cmd->str);
		free(paths_var);
		if (!exec->absolute_cmd && access(cmd_tmp, X_OK) == 0)
			exec->absolute_cmd = ft_strdup(cmd_tmp);
		free(cmd_tmp);
		++i;
	}
	free_ar(paths);
}

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

static void	child_proc(t_env *env, t_token *token, t_exec *exec)
{
	int		dup_ret;

	dup_ret = dup2(token->infile, STDIN_FILENO);
	if (dup_ret != -1)
		dup_ret = dup2(token->outfile, STDOUT_FILENO);
	close_fds(token);
	free_env(env);
	free_tokens(token);
	if (dup_ret != -1)
		execve(exec->absolute_cmd, exec->args, exec->env);
	free_exec(exec);
	exit(0);
}

int	exec_child(t_token *token, t_env *env)
{
	pid_t	pid;
	t_exec	*exec;
	int		exit_code;

	if (!token || !token->cmd)
		return (1);
	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (1);
	fill_valid_cmd(token->cmd, env, exec);
	fill_args(token->cmd, exec);
	fill_env(env, exec);
	pid = fork();
	if (!exec->absolute_cmd || !exec->env || !exec->args || pid < 0)
	{
		free_exec(exec);
		return (1);
	}
	if (pid == 0)
		child_proc(env, token, exec);
	close_fds(token);
	waitpid(pid, &exit_code, 0);
	free_exec(exec);
	return (exit_code);
}
