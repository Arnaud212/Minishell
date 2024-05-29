/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:41:55 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/23 18:09:01 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "cmd.h"

static int		pipeline_pipe_fork(t_list *iter, int pipes[2][2],
					t_list *l_free, t_env content);
static void		pipeline_element(t_list *element, int pipes[2][2],
					t_list *l_free, t_env content);
static t_env	pipeline_scmd(t_list *scmd, t_list *l_free, t_env content);

t_env	exec_pipeline(t_list *pipeline, t_list *l_free, t_env content)
{
	t_list	*iter;
	int		pipes[2][2];
	int		pid;

	exec_pipeline_pipes_init(pipes);
	pid = -1;
	content.i = 0;
	iter = cmd_content(pipeline)->l_element;
	while (iter)
	{
		pid = pipeline_pipe_fork(iter, pipes, l_free, content);
		if (pid == -1)
		{
			exec_pipeline_pipes_close(pipes, -1, false);
			break ;
		}
		exec_pipeline_pipes_close(pipes, content.i, (iter->next == NULL));
		iter = iter->next;
		content.i++;
	}
	content.status = exec_wait_for_all(pid);
	return (content);
}

static int	pipeline_pipe_fork(t_list *iter, int pipes[2][2],
				t_list *l_free, t_env content)
{
	int			pid;

	if (iter->next && pipe(pipes[content.i % 2]) < 0)
	{
		print_error_errno(SHELL_NAME, "pipe error", NULL);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		print_error_errno(SHELL_NAME, "fork error", NULL);
		return (-1);
	}
	if (pid == 0)
		pipeline_element(iter, pipes, l_free, content);
	return (pid);
}

static void	pipeline_element(t_list *element, int pipes[2][2],
				t_list *l_free, t_env content)
{
	int	fd[2];

	exec_pipeline_pipes_set(fd, pipes, content.i, (element->next == NULL));
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	exec_pipeline_pipes_close(pipes, -1, false);
	if (cmd_type(element) == CMD_SCMD)
		pipeline_scmd(element, l_free, content);
}

static t_env	pipeline_scmd(t_list *scmd, t_list *l_free, t_env content)
{
	char	**argv;

	if (exec_scmd_preperation(scmd, &argv, content) == ERROR)
		exec_scmd_free_exit(EXIT_FAILURE, argv, l_free, content);
	if (redir(scmd_content(scmd)->l_redir, NULL) == ERROR)
		exec_scmd_free_exit(EXIT_FAILURE, argv, l_free, content);
	if (!(scmd_content(scmd)->l_argv))
		exec_scmd_free_exit(EXIT_SUCCESS, argv, l_free, content);
	if (builtin_check(argv))
		content = builtin_exec(argv, l_free, content);
	else
		content = exec_scmd_exec(argv, content);
	exec_scmd_free_exit(content.status, argv, l_free, content);
	return (content);
}
