/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 09:53:43 by mcrenn            #+#    #+#             */
/*   Updated: 2026/06/08 14:13:12 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <unistd.h>

/*---------------------------QUOTE STATE--------------------------------------*/
typedef enum e_quote_state
{
	NO_QTE = 0,
	SIMPLE_QTE = 39,
	DOUBLE_QTE = 34
}	t_quote_state;

/*---------------------------STATUS-------------------------------------------*/
typedef enum e_status
{
	SUCCESS,
	FAILURE,
	BAD_ARG,
	ALLOCATION_FAILURE,
	PIPE_FAILURE
}	t_status;

/*---------------------------REDIRECTIONS-------------------------------------*/
typedef enum e_redirect
{
	NONE,
	INPUT,
	HEREDOC,
	TRUNC,
	APPEND,
	ERROR_REDIR
}	t_redirect;

typedef enum e_expand
{
	EXPAND,
	NO_EXPAND
}	t_expand;

/*---------------------------TOKEN COMMAND------------------------------------*/
typedef struct s_command
{
	char				*str;
	struct s_command	*next;
}						t_command;

/*---------------------------TOKEN--------------------------------------------*/
typedef struct s_token
{
		int				infile;
		int				outfile;
		t_command		*cmd;
		struct s_token	*next;
}					t_token;

/*---------------------------ENV----------------------------------------------*/
typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}					t_env;

/*---------------------------EXEC---------------------------------------------*/
typedef struct s_exec
{
	char			*absolute_cmd;
	char			**env;
	char			**args;
}					t_exec;

/*---------------------------PID LIST-----------------------------------------*/
typedef struct s_pid_list
{
	pid_t				pid;
	struct s_pid_list	*next;
}						t_pid_list;

/*---------------------------MINISHELL----------------------------------------*/
typedef struct s_minishell
{
	t_token	*tkn_node;
	t_env	*env;
	int		old_error_code;
}	t_minishell;

#endif
