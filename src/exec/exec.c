/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:41:55 by jchauvet          #+#    #+#             */
/*   Updated: 2023/07/20 10:05:08 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>

#include "exec.h"
#include "cmd.h"

t_env	exec_recursive(t_list *l_cmd, t_list *l_free, t_env content)
{
	if (cmd_type(l_cmd) == CMD_SCMD)
	{
		content = exec_scmd(l_cmd, l_free, content);
		exec_exit_status_set(content.status);
	}
	else if (cmd_type(l_cmd) == CMD_PIPELINE)
	{
		content = exec_pipeline(l_cmd, l_free, content);
		exec_exit_status_set(content.status);
	}
	if (l_cmd->next)
	{
		l_cmd = l_cmd->next;
		if (l_cmd != NULL)
		{
			content = exec_recursive(l_cmd->next, l_free, content);
			exec_exit_status_set(content.status);
		}
	}
	exec_exit_status_get();
	return (content);
}

void	exec_free_all(char **argv, t_list *l_free, t_env content)
{
	struct stat	buf;

	if (argv)
		ft_free_split(&argv);
	if (l_free)
		ft_lstclear(&l_free, c_cmd_destroy);
	if (content.env)
		ft_free_split(&content.env);
	rl_clear_history();
	if (fstat(STDIN_FILENO, &buf) != -1)
		close(STDIN_FILENO);
	if (fstat(STDOUT_FILENO, &buf) != -1)
		close(STDOUT_FILENO);
	if (fstat(STDERR_FILENO, &buf) != -1)
		close(STDERR_FILENO);
}
