/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:36:18 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/21 17:04:10 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "env.h"

int	expand_var(t_c_scmd *c_scmd, t_env content)
{
	int		status;

	status = expand_var_token_list(c_scmd->l_argv, content);
	if (status != ERROR)
		status = expand_var_token_list(c_scmd->l_redir, content);
	if (status != ERROR)
		status = expand_var_splitting(&(c_scmd->l_argv));
	if (status != ERROR)
		status = expand_var_splitting(&(c_scmd->l_redir));
	return (status);
}

int	check_token(t_c_token *c_token, int *i)
{
	if (c_token->str[*i] == '$' && (env_is_var_char(c_token->str[*i + 1])
			|| (c_token->str[*i + 1] == '\0'
				&& !(c_token->flags & (TOK_S_QUOTE | TOK_D_QUOTE))
				&& c_token->flags & TOK_CONNECTED)))
		return (1);
	return (0);
}
