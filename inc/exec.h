/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:39:30 by jchauvet          #+#    #+#             */
/*   Updated: 2023/07/11 14:47:13 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "global.h"
# include "redir.h"
# include "env.h"
# define EXEC_NOEXEC	126
# define EXEC_NOTFOUND	127

t_env	exec_recursive(t_list *l_cmd, t_list *l_free, t_env content);
void	exec_free_all(char **argv, t_list *l_free, t_env content);
void	exec_exit_status_set(int status);
int		exec_exit_status_get(void);
void	exec_pipeline_pipes_init(int pipes[2][2]);
void	exec_pipeline_pipes_set(int fd[2], int pipes[2][2], int i, bool last);
void	exec_pipeline_pipes_close(int pipes[2][2], int i, bool last);
t_env	exec_pipeline(t_list *pipeline, t_list *l_free, t_env content);
int		exec_scmd_search_path(char **argv, t_env content);
t_env	exec_scmd(t_list *scmd, t_list *l_free, t_env content);
int		exec_scmd_preperation(t_list *scmd, char ***argv, t_env content);
t_env	exec_scmd_exec(char **argv, t_env content);
void	exec_scmd_free_exit(int status, char **argv,
			t_list *l_free, t_env content);
int		exec_wait_pid(int last_pid, char *name);
int		exec_wait_for_all(int last_pid);

void	util_one(t_list *scmd, char **argv, t_list *l_free, t_env content);
int		util_two(t_list *scmd, t_env content);
#endif
