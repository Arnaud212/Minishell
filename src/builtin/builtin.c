/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:03:15 by agiraud           #+#    #+#             */
/*   Updated: 2023/06/23 18:13:38 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"

int	builtin_check(char **cmd)
{
	if (cmd[0] && (ft_strcmp(cmd[0], "exit") == 0))
		return (1);
	else if (cmd[0] && (ft_strcmp(cmd[0], "cd") == 0))
		return (1);
	else if (cmd[0] && (ft_strcmp(cmd[0], "pwd") == 0))
		return (1);
	else if (cmd[0] && (ft_strcmp(cmd[0], "env") == 0))
		return (1);
	else if (cmd[0] && (ft_strcmp(cmd[0], "export") == 0))
		return (1);
	else if (cmd[0] && (ft_strcmp(cmd[0], "unset") == 0))
		return (1);
	else if (cmd[0] && (ft_strcmp(cmd[0], "echo") == 0))
		return (1);
	return (0);
}

t_env	builtin_exec(char **argv, t_list *l_free, t_env content)
{
	content.status = exec_exit_status_get();
	if (argv[0] && (ft_strcmp(argv[0], "exit") == 0))
		content = ft_exit(argv, content.status, l_free, content);
	else if (argv[0] && (ft_strcmp(argv[0], "cd") == 0))
		content = ft_cd(argv, content);
	else if (argv[0] && (ft_strcmp(argv[0], "pwd") == 0))
		content = ft_pwd(content);
	else if (argv[0] && (ft_strcmp(argv[0], "env") == 0))
		content = ft_env(argv, content);
	else if (argv[0] && (ft_strcmp(argv[0], "export") == 0))
		content = ft_export(argv, content);
	else if (argv[0] && (ft_strcmp(argv[0], "unset") == 0))
		content = ft_unset(argv, content);
	else if (argv[0] && (ft_strcmp(argv[0], "echo") == 0))
		content = ft_echo(argv, content);
	return (content);
}
