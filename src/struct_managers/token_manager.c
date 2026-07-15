/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:45:23 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/15 10:08:25 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free every token and their attributes in the 'tokens' list
 *
 * @param tokens List of tokens to be executed
 */
void	free_tokens(t_token **tokens)
{
	lst_clear_tkn(tokens);
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
void	close_fds(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->infile > 2)
		{
			close(tokens->infile);
			tokens->infile = -1;
		}
		if (tokens->outfile > 2)
		{
			close(tokens->outfile);
			tokens->outfile = -1;
		}
		tokens = tokens->next;
	}
}

/**
 * @brief Jumps to the next token in the list, freeing and closing fds behind.
 *
 * @param token Actual token node
 * @return Next token node to execute
 */
void	jump_next_token(t_token **token)
{
	t_token	*ret;

	if ((*token)->infile > 2)
		close((*token)->infile);
	if ((*token)->outfile > 2)
		close((*token)->outfile);
	lst_clear_cmd(&(*token)->cmd);
	ret = (*token)->next;
	free(*token);
	*token = ret;
}
