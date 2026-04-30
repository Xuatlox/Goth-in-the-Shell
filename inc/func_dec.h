/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_dec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:15:32 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/30 12:52:57 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_DEC_H
# define FUNC_DEC_H

# include "struct.h"
# include <stdlib.h>

// EXEC FUNCTION
int			execute(t_token *tokens, t_env *env);
int			exec_pipe(t_token *tokens, t_env *env);
int			exec_child(t_token *token, t_env *env);
int			dispatch(t_token *token, t_env *env);

// EXEC_CHILD UTILS
void		clean_child(t_env *env, t_token *token);

// CMD MANAGEMENT
int			get_cmd_size(const t_command *cmd);

// ENV MANAGEMENT
int			get_env_size(const t_env *env);
char		**get_env(t_env *env, const char *name);
void		set_env(const char *var_name, char *new_val, t_env *env);
void		add_env(t_env *env, char *name, char *value);
void		free_env_tokens(t_env *env, t_token *token);

// BUILTIN CMDS
int			exec_cd(const t_command *args, int fd_out, t_env *env);
int			exec_echo(t_command *args, int fd_out);
int			exec_export(const t_command *args, int fd_out, t_env *env);
int			exec_env(const t_command *args, int fd_out, const t_env *env);
int			exec_pwd(int fd_out, t_env *env);
int			exec_unset(const t_command *args, t_env *env);
int			exec_exit(t_token *token, t_env *env);

// SIGNALS
int			detect_sig(void);

// LEXER
t_token		*lexer(char* cmd, t_status *status);
t_status	charjoin(t_command *src, char c);
t_redirect	check_redirect(char *str);
t_status	str_charjoin(char **src, char c);
void		check_quotes(char c, t_quote_state *quote_state);
t_token		*parsing(char *line, t_status *status);
void		redirect_manager(char *str, t_token *tkn_node, t_status *status, size_t *i);

// LST
t_token		*lst_newtoken(t_status *status);
t_command	*lst_newcommand(char c, t_status *status);
t_token		*ft_lstlast_token(t_token *lst);
void		ft_lstadd_token(t_token **lst, t_status *status);
void		ft_lstadd_command(t_token *last_tkn, char c, t_status *status);
void		ft_lstadd_redirect(t_token *last_tkn, char *cmd, t_redirect redirect,
			t_status *status);
void		lst_clear_tkn(t_token **tkn);
void		lst_clear_cmd(t_command **cmd);

// ERRORS
void		error_parsing(char c);

#endif
