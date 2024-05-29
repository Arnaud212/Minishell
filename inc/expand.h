/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:32:21 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/21 17:03:59 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "global.h"
# include "cmd.h"
# include "env.h"
# define VAR_SPACE	-1

int		expand_var(t_c_scmd *c_scmd, t_env content);
int		expand_var_splitting(t_list **l_token);
int		expand_var_token_list(t_list *l_token, t_env content);
char	*expand_pattern_get(t_list *token);
char	**expand_files_current_dir(void);
int		check_token(t_c_token *c_token, int *i);
#endif
