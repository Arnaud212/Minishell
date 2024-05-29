/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:40:18 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/14 08:56:03 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "global.h"

# define TOK_TEXT			1
# define TOK_S_QUOTE		2
# define TOK_D_QUOTE		4
# define TOK_REDIR_FILE		8
# define TOK_CONNECTED		16
# define TOK_PIPE			32
# define TOK_REDIR			64
# define TOK_HEREDOC		128

typedef struct s_token_content
{
	int		flags;
	char	*str;
}	t_c_token;

t_list		*token_create(char *string, int type);
t_c_token	*token_content(t_list *token);
void		c_token_destroy(void *c_token);
bool		token_is_cmd(t_list *token);
char		*token_to_str(t_list *l_token);
char		**l_token_to_split(t_list *l_token);

#endif
