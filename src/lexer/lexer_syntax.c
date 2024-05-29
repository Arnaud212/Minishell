/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:43:25 by jchauvet          #+#    #+#             */
/*   Updated: 2023/03/03 17:37:54 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* CHECKING SYNTAX (MAKING SURE THERE ISN'T BROKEN PIPES.)*/

static int	syntax_pipe(t_list *l_token);

int	lexer_syntax_check(t_list *l_token)
{
	if (syntax_pipe(l_token) == ERROR)
		return (ERROR);
	return (0);
}

static int	syntax_pipe(t_list *l_token)
{
	if (l_token && token_content(l_token)->flags & TOK_PIPE)
		return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_PIPE));
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_PIPE)
		{
			if (l_token->next == NULL)
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_PIPE));
			else if (token_content(l_token->next)->flags
				& (TOK_PIPE))
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_PIPE));
		}
		l_token = l_token->next;
	}
	return (0);
}
