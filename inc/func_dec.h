/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_dec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:15:32 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/09 17:50:53 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_DEC_H
#define FUNC_DEC_H

#include "struct.h"

int		exec_cd(const t_command *command, int fd_out, t_env *env);
char	**get_env(t_env *env, const char *name);
void	set_env(const char *var_name, char *new_val, t_env *env);

// BUILTIN CMDS
int		exec_cd(const t_command *args, int fd_out, t_env *env);
int		exec_export(const t_command *args, int fd_out, t_env *env);

t_token	*ft_lst_token(int infile, int outfile, char *cmd);

#endif
