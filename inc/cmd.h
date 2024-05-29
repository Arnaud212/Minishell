/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:39:05 by jchauvet          #+#    #+#             */
/*   Updated: 2023/02/24 09:38:49 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "global.h"
# include "token.h"

# define CMD_SCMD		1
# define CMD_PIPE		2
# define CMD_PIPELINE	4
# define CMD_L_SCMD		8
# define CMD_L_CMD		16

typedef struct s_scmd_content
{
	int		type;
	t_list	*l_argv;
	t_list	*l_redir;
}	t_c_scmd;

typedef struct s_cmd_content
{
	int		type;
	t_list	*l_element;
}	t_c_cmd;

t_list		*cmd_create(int type);
t_c_cmd		*cmd_content(t_list *cmd);
void		c_cmd_destroy(void *c_cmd);
int			cmd_type(t_list *cmd);
int			cmd_type_from_token(t_list *token);
t_list		*scmd_create(int type);
t_c_scmd	*scmd_content(t_list *element);
void		c_scmd_destroy(void *c_element);

#endif
