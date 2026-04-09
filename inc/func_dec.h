/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_dec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:15:32 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/09 13:02:41 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_DEC_H
#define FUNC_DEC_H

#include "struct.h"

int		exec_cd(const t_command *command, int fd_out, t_env *env);
char	**get_env(t_env *env, const char *name);

t_token	*ft_lst_token(int infile, int outfile, char *cmd);

#endif
s
