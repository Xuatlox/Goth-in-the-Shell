/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:45:23 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/01 14:49:22 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free every token and their attributes in the 'tokens' list
 *
 * @param tokens List of tokens to be executed
 */
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
			if (tokens->cmd->str)
				free(tokens->cmd->str);
			free(tokens->cmd);
			tokens->cmd = tmp_cmd;
		}
		free(tokens);
		tokens = tmp_tkn;
	}
}

/**
 * @brief Counts the number of nodes in the 'tokens' list
 *
 * @param tokens List of tokens to be executed
 * @return Length of 'tokens', or 0 if NULL
 */
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

/**
 * @brief Counts the number of nodes in the 'cmd' list
 *
 * @param cmd List of arguments of a command to execute
 * @return Length of 'cmd', or 0 if NULL
 */
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

/**
 * @brief Close every fds in the 'tokens' list
 *
 * @param tokens List of tokens to be executed
 */
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

/**
 * @brief Jumps to the next token in the list, freeing and closing fds behind.
 *
 * @param token Actual token node
 * @return Next token node to execute
 */
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
