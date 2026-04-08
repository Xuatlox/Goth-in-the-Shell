/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 09:53:43 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/08 10:49:03 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token
{
	WORD,
	PIPE
}	t_type_token;

typedef struct s_token
{
	char			*str;
	t_type_token	token;
	struct s_token	*next;
}					t_token;
