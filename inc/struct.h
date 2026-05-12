/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 09:53:43 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/07 11:34:12 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token
{
	WORD,
	PIPE
}	t_type_token;

typedef enum e_quote_state
{
	NO_QTE = 0,
	SIMPLE_QTE = 39,
	DOUBLE_QTE = 34
}	t_quote_state;

typedef enum e_status
{
	SUCCESS,
	FAILURE,
	BAD_ARG,
	ALLOCATION_FAILURE,
	PIPE_FAILURE
}	t_status;

typedef enum e_redirect
{
	NONE,
	INPUT,
	HEREDOC,
	TRUNC,
	APPEND
}	t_redirect;

typedef struct s_command
{
	char				*str;
	struct s_command	*next;
}						t_command;

typedef struct s_token
{
		int				infile;
		int				outfile;
		t_command		*cmd;
		struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}					t_env;
