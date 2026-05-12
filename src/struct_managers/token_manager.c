/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:45:23 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/07 14:05:22 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token		*tmp_tkn;
	t_command	*tmp_cmd;

	while (tokens)
	{
		tmp_tkn = tokens->next;
		while (tokens->cmd)
		{
			tmp_cmd = tokens->cmd->next;
			free(tokens->cmd->str);
			free(tokens->cmd);
			tokens->cmd = tmp_cmd;
		}
		free(tokens);
		tokens = tmp_tkn;
	}
}

int	tokens_len(const t_token *tokens)
{
	int		size;

	size = 0;
	while (tokens)
	{
		++size;
		tokens = tokens->next;
	}
	return (size);
}

int	cmd_len(const t_command *cmd)
{
	int	size;

	size = 0;
	while (cmd)
	{
		++size;
		cmd = cmd->next;
	}
	return (size);
}

void	close_fds(const t_token *tokens)
{
	while (tokens)
	{
		if (tokens->infile > 2)
			close(tokens->infile);
		if (tokens->outfile > 2)
			close(tokens->outfile);
		tokens = tokens->next;
	}
}

t_token	*jump_next_token(t_token *token)
{
	t_token		*ret;
	t_command	*cmd_tmp;

	if (token->infile > 2)
		close(token->infile);
	if (token->outfile > 2)
		close(token->outfile);
	while (token->cmd)
	{
		cmd_tmp = token->cmd->next;
		free(token->cmd->str);
		free(token->cmd);
		token->cmd = cmd_tmp;
	}
	ret = token->next;
	free(token);
	return (ret);
}
