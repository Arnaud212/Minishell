/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:41:55 by jchauvet          #+#    #+#             */
/*   Updated: 2023/07/11 14:47:45 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "exec.h"
#include "builtin.h"
#include "cmd.h"
#include "env.h"
#include "expand.h"
#include "signals.h"

static t_env	exec_builtin(t_list *scmd, char **argv,
					t_list *l_free, t_env content);

t_env	exec_scmd(t_list *scmd, t_list *l_free, t_env content)
{
	char	**argv;
	int		pid;

	if (exec_scmd_preperation(scmd, &argv, content) == ERROR)
	{
		content.status = ERROR;
		return (content);
	}
	if (util_two(scmd, content) == 1)
		return (content);
	if (builtin_check(argv))
		return (exec_builtin(scmd, argv, l_free, content));
	pid = fork();
	if (pid == -1)
		ft_free_split(&argv);
	if (pid == -1)
	{
		content.status = print_error_errno(SHELL_NAME, NULL, NULL);
		return (content);
	}
	if (pid == 0)
		util_one(scmd, argv, l_free, content);
	content.status = exec_wait_pid(pid, argv[0]);
	ft_free_split(&argv);
	return (content);
}

int	exec_scmd_preperation(t_list *scmd, char ***argv, t_env content)
{
	t_list	*l_redir_undo;
	int		status;

	status = 0;
	*argv = NULL;
	if (expand_var(scmd_content(scmd), content) == ERROR)
		return (ERROR);
	if (scmd_content(scmd)->l_argv)
	{
		*argv = l_token_to_split(scmd_content(scmd)->l_argv);
		if (*argv == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	}
	else if (scmd_content(scmd)->l_redir)
	{
		status = redir(scmd_content(scmd)->l_redir, &l_redir_undo);
		if (redir_undo(&l_redir_undo) == ERROR)
			status = ERROR;
	}
	return (status);
}

t_env	exec_scmd_exec(char **argv, t_env content)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	termios_change(true);
	if (!ft_strchr(argv[0], '/') && env_get_value("PATH", content.env) != NULL)
	{
		if (exec_scmd_search_path(argv, content) == ERROR)
		{
			print_error(SHELL_NAME, argv[0], NULL, "command not found");
			content.status = EXEC_NOTFOUND;
			return (content);
		}
	}
	execve(argv[0], argv, content.env);
	if (errno == ENOENT)
		content.status = EXEC_NOTFOUND;
	else
		content.status = EXEC_NOEXEC;
	print_error_errno(SHELL_NAME, argv[0], NULL);
	return (content);
}

void	exec_scmd_free_exit(int status, char **argv,
			t_list *l_free, t_env content)
{
	exec_free_all(argv, l_free, content);
	exit(status);
}

static t_env	exec_builtin(t_list *scmd, char **argv,
					t_list *l_free, t_env content)
{
	t_list	*l_redir_undo;

	if (builtin_check(argv))
	{
		content.status = redir(scmd_content(scmd)->l_redir, &l_redir_undo);
		if (content.status != ERROR)
			content = builtin_exec(argv, l_free, content);
		if (redir_undo(&l_redir_undo) == ERROR)
			content.status = ERROR;
		ft_free_split(&argv);
		return (content);
	}
	else
	{
		content.status = ERROR;
		return (content);
	}
}
