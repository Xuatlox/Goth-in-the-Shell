/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:32:59 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/10 15:13:34 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	redirect_outfile(t_token *tkn_node, t_redirect redir, char *file_name)
{
	if (tkn_node->outfile != -1)
		close(tkn_node->outfile);
	if (redir == TRUNC)
	{
		tkn_node->outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tkn_node->outfile == -1)
		{
			free(file_name);
			return (FAILURE);
		}
	}
	if (redir == APPEND)
	{
		tkn_node->outfile = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tkn_node->outfile == -1)
		{
			free(file_name);
			return (FAILURE);
		}
	}
	free(file_name);
	return (SUCCESS);
}

static t_status	redirect_infile(t_token *tkn_node, t_redirect redir, char *file_name, t_env *env)
{
	if (tkn_node->infile != -1)
		close(tkn_node->infile);
	if (redir == INPUT)
	{
		tkn_node->infile = open(file_name, O_RDONLY);
		if (tkn_node->infile == -1)
		{
			free(file_name);
			return (FAILURE);
		}
	}
	if (redir == HEREDOC)
	{
		tkn_node->infile = pipe_heredoc(file_name, env);
		if (tkn_node->infile == -1)
		{
			free(file_name);
			return (FAILURE);
		}
	}
	free(file_name);
	return (SUCCESS);
}

t_status	redirect_manager(char *str, t_token *tkn_node, size_t *i, t_env *env)
{
	t_redirect	redir_state;
	t_status	status;
	char		*new_word;

	new_word = NULL;
	// if (ft_lstlast_command(ft_lstlast_token(tkn_node)) == NULL)
	// 	ft_lstlast_token(tkn_node)->cmd = lst_newcommand(0, status);
	// else
	// 	ft_lstlast_command(ft_lstlast_token(tkn_node)->cmd);
	redir_state = check_redirect(&str[*i]);
	if (redir_state == HEREDOC || redir_state == APPEND)
		(*i)++;
	(*i)++;
	while (str[*i] && ft_isspace(str[*i]) == 1)
		(*i)++;
	while (str[*i] && ft_isspace(str[*i]) == 0)
	{
		if (str_charjoin(&new_word, str[*i]) != SUCCESS)
		{
			if (new_word)
				free(new_word);
			return (ALLOCATION_FAILURE);
		}
		(*i)++;
	}
	if (redir_state == INPUT || redir_state == HEREDOC)
		status = redirect_infile(tkn_node, redir_state, new_word, env);
	else
		status = redirect_outfile(tkn_node, redir_state, new_word);
	return (status);
}
