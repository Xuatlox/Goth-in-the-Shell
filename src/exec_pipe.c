/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:19:28 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/30 13:43:48 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void	clean_post_exec(t_env *env, t_token *tokens)
{
	t_env		*tmp_env;
	t_token		*tmp_token;
	t_command	*tmp_cmd;

	while (env)
	{
		tmp_env = env->next;
		free(env->name);
		free(env->val);
		free(env);
		env = tmp_env;
	}
	while (tokens)
	{
		tmp_token = tokens->next;
		while (tokens->cmd)
		{
			tmp_cmd = tokens->cmd->next;
			free(tokens->cmd->str);
			free(tokens->cmd);
			tokens->cmd = tmp_cmd;
		}
		free(tokens);
		tokens = tmp_token;
	}
}

static int	tokens_len(const t_token *tokens)
{
	int		size;

	size = 0;
	while (tokens)
	{
		tokens = tokens->next;
		++size;
	}
	return (size);
}

static int	wait_all(const pid_t *pid)
{
	int		status;

	while (*pid)
	{
		waitpid(*pid, &status, 0);
		++pid;
	}
	status = WEXITSTATUS(status);
	return (status);
}

static int	exec_all(t_token *tokens, t_env *env, pid_t **pid)
{
	int		ret;
	int		i;
	t_token	*head;

	i = 0;
	head = tokens;
	while (tokens)
	{
		(*pid)[i] = fork();
		if ((*pid)[i] < 0)
		{
			free(*pid);
			return (0);
		}
		if ((*pid)[i] == 0)
		{
			free(*pid);
			ret = dispatch(tokens, env);
			clean_post_exec(env, head);
			exit(ret);
		}
		++i;
		tokens = tokens->next;
	}
	return (1);
}

int	exec_pipe(t_token *tokens, t_env *env)
{
	pid_t	*pid;
	int		size;
	int		ret;

	size = tokens_len(tokens);
	pid = ft_calloc(size + 1, sizeof(pid_t));
	if (!pid || !exec_all(tokens, env, &pid))
		return (0);
	while (tokens)
	{
		close(tokens->infile);
		close(tokens->outfile);
		tokens = tokens->next;
	}
	ret = wait_all(pid);
	free(pid);
	return (ret);
}
