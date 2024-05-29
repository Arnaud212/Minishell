/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:39:54 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/21 17:13:04 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"
# include "cmd.h"
# include "token.h"
# include "env.h"

t_list	*parser(t_list *l_token, t_env content);
int		parser_heredoc(t_list *l_token);
int		parser_cmd_pipeline_merge(t_list **l_cmd);
t_list	*parser_scmd_tokens(t_list *l_token);

#endif
