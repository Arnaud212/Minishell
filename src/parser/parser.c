/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:44:17 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/21 17:14:00 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "printer.h"
#include "global.h"

/* PARSER TAKES THE LEXED (TOKENIZED) INPUT AND CREATES A LIST OF COMMANDS*/
/* BREAKING THEM DOWN IN SUBCOMMANDS (SCMDS) FOR EASE OF USE.*/
/* MAKING SURE THAT PIPES AND REDIRS (AND HEREDOC) ARE  HANDLED.*/

static int	parser_recursive_merge(t_list **l_cmd, t_env content);

t_list	*parser(t_list *l_token, t_env content)
{
	t_list	*l_cmd;

	l_cmd = parser_scmd_tokens(l_token);
	if (l_cmd == NULL)
		return (NULL);
	if (env_var_is_value(DEBUG_ENV, "printer", content.env))
	{
		printer_cmd(l_cmd);
		printer_structure(l_cmd);
	}
	if (parser_recursive_merge(&l_cmd, content) == ERROR)
	{
		ft_lstclear(&l_cmd, c_cmd_destroy);
		return (NULL);
	}
	if (env_var_is_value(DEBUG_ENV, "printer", content.env))
	{
		printer_cmd(l_cmd);
		ft_putchar_fd('\n', 1);
	}
	return (l_cmd);
}

static int	parser_recursive_merge(t_list **l_cmd, t_env content)
{
	int	pipeline;

	pipeline = 1;
	while (pipeline > 0)
	{
		pipeline = parser_cmd_pipeline_merge(l_cmd);
		if (pipeline == ERROR)
			return (ERROR);
		if (pipeline > 0 && env_var_is_value(DEBUG_ENV, "printer", content.env))
			printer_structure(*l_cmd);
	}
	return (0);
}
