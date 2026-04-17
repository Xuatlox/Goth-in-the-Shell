/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_dec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:15:32 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/17 13:44:35 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_DEC_H
# define FUNC_DEC_H

# include "struct.h"
# include <stdlib.h>

int			exec_cd(const t_command *command, int fd_out, t_env *env);
char		**get_env(t_env *env, const char *name);
void		set_env(const char *var_name, char *new_val, t_env *env);

// BUILTIN CMDS
int			exec_cd(const t_command *args, int fd_out, t_env *env);
int			exec_export(const t_command *args, int fd_out, t_env *env);

// LEXER
t_token		*lexer(char* cmd, t_status *status);
t_status	charjoin(t_command *src, char c);
t_redirect	check_redirect(char *str);
void		check_quotes(char c, t_quote_state *quote_state);
// LST
t_token		*lst_newtoken(t_status *status);
t_command	*lst_newcommand(char c, t_status *status);
t_token		*ft_lstlast_token(t_token *lst);
void		ft_lstadd_token(t_token **lst, t_status *status);
void		ft_lstadd_command(t_token *last_tkn, char c, t_status *status);
void		ft_lstadd_redirect(t_token *last_tkn, char *cmd, t_redirect redirect,
			t_status *status);

#endif
