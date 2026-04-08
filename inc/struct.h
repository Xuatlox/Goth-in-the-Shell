/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 09:53:43 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/08 13:40:15 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token
{
	WORD,
	PIPE
}	t_type_token;

typedef struct s_command
{
	char				*cmd;
	struct s_command	*next;
}						t_command;

typedef struct s_token
{
	int				infile;
	int				outfile;
	t_command		*str;
	struct s_token	*next;
}					t_token;
