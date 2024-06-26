/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_scmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:44:29 by jchauvet          #+#    #+#             */
/*   Updated: 2023/02/24 09:54:21 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include "cmd.h"

/* FOR DEBUG PURPOSES ONLY */

static void	printer_scmd_argv(t_list *l_argv);
static void	printer_scmd_redir(t_list *l_redir);

void	printer_scmd(t_c_scmd *scmd)
{
	printer_scmd_argv(scmd->l_argv);
	printer_scmd_redir(scmd->l_redir);
}

void	printer_other(int type)
{
	if (type == CMD_PIPE)
		printf("\033[0;31m| \033[m");
	else
		printf("ERROR ");
}

void	printer_scmd_pipeline(t_list *l_scmd_pipeline, bool newline)
{
	while (l_scmd_pipeline)
	{
		printer_scmd(scmd_content(l_scmd_pipeline));
		if (l_scmd_pipeline->next)
			printer_other(CMD_PIPE);
		l_scmd_pipeline = l_scmd_pipeline->next;
	}
	if (newline)
		printf("\n");
}

static void	printer_scmd_argv(t_list *l_argv)
{
	bool	command;

	command = true;
	while (l_argv)
	{
		if (command == true)
		{
			printf("\033[0;33m%s \033[m", token_content(l_argv)->str);
			command = false;
		}
		else
			printf("\033[0;32m%s \033[m", token_content(l_argv)->str);
		l_argv = l_argv->next;
	}
}

static void	printer_scmd_redir(t_list *l_redir)
{
	while (l_redir)
	{
		if (token_content(l_redir)->flags & TOK_REDIR)
			printf("\033[0;35m%s \033[m", token_content(l_redir)->str);
		else
		{
			if (token_content(l_redir)->flags & TOK_HEREDOC)
				printf("\033[0;34mhere_doc \033[m");
			else
				printf("\033[0;34m%s \033[m", token_content(l_redir)->str);
		}
		l_redir = l_redir->next;
	}
}
