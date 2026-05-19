/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_dec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:15:32 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/19 12:55:37 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_DEC_H
# define FUNC_DEC_H

# include "struct.h"
# include <stdlib.h>

// EXEC FUNCTION
int			execute(t_token *tokens, t_env **env);
int			exec_pipe(t_token *tokens, t_env **env);
int			exec_child(t_token *token, t_env *env);
int			dispatch(t_token *token, t_env **env);

// EXEC_PIPE UTILS
void		pipe_child_proc(t_token *tokens, t_env *env);

// EXEC_CHILD UTILS
void		clean_child(t_env *env, t_token *token);
int			manage_child(t_env *env, t_token *token, t_exec *exec);

// EXEC MANAGEMENT
void		free_exec(t_exec *exec);

// TOKEN MANAGEMENT
int			cmd_len(const t_command *cmd);
void		free_tokens(t_token *tokens);
int			tokens_len(const t_token *tokens);
void		close_fds(const t_token *tokens);
t_token		*jump_next_token(t_token *token);

// ENV MANAGEMENT
int			get_env_size(const t_env *env);
char		**get_env(t_env *env, const char *name);
void		set_env(const char *var_name, char *new_val, t_env *env);
int			add_env(t_env *env, char *name, char *value);
void		free_env(t_env *env);
t_env		*build_env(char **envp);
t_env		*new_env(char *name, char *value);

// BUILTIN CMDS
int			exec_cd(const t_command *args, int fd_out, t_env *env);
int			exec_echo(t_command *args, int fd_out);
int			exec_export(const t_command *args, int fd_out, t_env **env);
int			exec_env(int fd_out, const t_env *env);
int			exec_pwd(int fd_out, t_env *env);
int			exec_unset(const t_command *args, t_env **env);
int			exec_exit(t_token *token, t_env *env);

// SIGNALS
int			detect_sig(void);

// PARSING
t_token		*parsing(char *line, t_status *status, t_minishell *minishell);
t_token		*lexer(char* cmd, t_status *status, t_env *env);
t_status	charjoin(t_command *src, char c);
t_redirect	check_redirect(char *str);
t_status	str_charjoin(char **src, char c);
int			check_quotes(char c, t_quote_state *quote_state);
t_status	redirect_manager(char *str, t_token *tkn_node, size_t *i, t_env *env);
int			pipe_heredoc(char *delimiter, t_env *env);
void		expand(t_minishell *minishell, t_status *status);
void		remove_quotes(t_token *tkn_node, t_status *status);
char		*make_env_val(t_minishell *minishell, char *env_var);
char		*make_env_var(char *str);
size_t		ft_strlen_bash(char *str);

// LST
t_token		*lst_newtoken(t_status *status);
t_command	*lst_newcommand(char c, t_status *status);
t_command	*ft_lstlast_command(t_command *lst);
t_token		*ft_lstlast_token(t_token *lst);
void		ft_lstadd_token(t_token **lst, t_status *status);
void		ft_lstadd_command(t_token *last_tkn, char c, t_status *status);
void		ft_lstadd_redirect(t_token *last_tkn, char *cmd, t_redirect redirect,
			t_status *status);
void		lst_clear_tkn(t_token **tkn);
void		lst_clear_cmd(t_command **cmd);

// ERRORS
void		error_parsing(char c);
void		error_heredoc(char *s);

#endif
