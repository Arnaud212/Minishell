/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:43:01 by jchauvet          #+#    #+#             */
/*   Updated: 2023/07/11 14:47:03 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "cmd.h"

void	util_one(t_list *scmd, char **argv, t_list *l_free, t_env content)
{
	if (redir(scmd_content(scmd)->l_redir, NULL) == ERROR)
		exec_scmd_free_exit(EXIT_FAILURE, argv, l_free, content);
	content = exec_scmd_exec(argv, content);
	exec_scmd_free_exit(content.status, argv, l_free, content);
}

int	util_two(t_list *scmd, t_env content)
{
	(void)content;
	if (!(scmd_content(scmd)->l_argv))
	{
		content.status = 0;
		return (1);
	}
	return (0);
}
