/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:57:56 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/17 10:33:12 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "func_dec.h"

extern int	g_sig_ind;

#endif
