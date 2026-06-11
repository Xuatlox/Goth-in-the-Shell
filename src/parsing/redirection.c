/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:32:59 by mcrenn            #+#    #+#             */
/*   Updated: 2026/06/11 16:53:35 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	redirect_outfile(t_token *tkn_node, t_redirect redir,
	char *file_nme)
{
	if (tkn_node->outfile != -1)
		close(tkn_node->outfile);
	if (redir == TRUNC)
	{
		tkn_node->outfile = open(file_nme, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tkn_node->outfile == -1)
		{
			error_file(file_nme);
			free(file_nme);
			return (FAILURE);
		}
	}
	if (redir == APPEND)
	{
		tkn_node->outfile = open(file_nme, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tkn_node->outfile == -1)
		{
			error_file(file_nme);
			free(file_nme);
			return (FAILURE);
		}
	}
	free(file_nme);
	return (SUCCESS);
}

static t_status	redirect_infile(t_token *tkn_node, t_redirect redir,
	char *file_name, t_minishell *shell)
{
	if (tkn_node->infile != -1)
		close(tkn_node->infile);
	if (redir == INPUT)
	{
		tkn_node->infile = open(file_name, O_RDONLY);
		if (tkn_node->infile == -1)
		{
			error_file(file_name);
			free(file_name);
			return (FAILURE);
		}
	}
	if (redir == HEREDOC)
	{
		tkn_node->infile = pipe_heredoc(file_name, shell);
		if (tkn_node->infile == -1)
		{
			error_file(file_name);
			free(file_name);
			return (FAILURE);
		}
	}
	free(file_name);
	return (SUCCESS);
}

static t_status	make_word(char **new_word, char *str, size_t *i)
{
	while (str[*i] && ft_isspace(str[*i]) == 1)
		(*i)++;
	while (str[*i] && ft_isspace(str[*i]) == 0)
	{
		if (str_charjoin(new_word, str[*i]) != SUCCESS)
		{
			if (new_word)
				free(new_word);
			return (ALLOCATION_FAILURE);
		}
		(*i)++;
	}
	if (!*new_word)
	{
		error_parsing(0);
		return (BAD_ARG);
	}
	return (SUCCESS);
}

t_status	redirect_manager(char *str, t_token *tkn_node,
	size_t *i, t_minishell *shell)
{
	t_redirect	redir_state;
	t_status	status;
	char		*new_word;

	new_word = NULL;
	status = SUCCESS;
	redir_state = check_redirect(&str[*i]);
	if (redir_state == ERROR_REDIR)
		return (BAD_ARG);
	if (redir_state == HEREDOC || redir_state == APPEND)
		(*i)++;
	(*i)++;
	status = make_word(&new_word, str, i);
	if (redir_state != HEREDOC && status == SUCCESS)
	{
		check_expand(&new_word, shell, &status, 1);
		qte_remove(&new_word);
	}
	if (ft_lstlast_command(tkn_node->cmd) == NULL)
		tkn_node->cmd = lst_newcommand(0, &status);
	if ((redir_state == INPUT || redir_state == HEREDOC) && !status)
		status = redirect_infile(tkn_node, redir_state, new_word, shell);
	else if ((redir_state == TRUNC || redir_state == APPEND) && !status)
		status = redirect_outfile(tkn_node, redir_state, new_word);
	return (status);
}
