/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:46:27 by agiraud           #+#    #+#             */
/*   Updated: 2023/07/11 15:26:15 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <readline/readline.h>

# include "cmd.h"
# include "exec.h"
# include "global.h"
# include "env.h"

int			builtin_check(char **cmd);
t_env		builtin_exec(char **argv, t_list *l_free, t_env content);
t_env		ft_exit(char **argv, int status, t_list *l_free, t_env content);
int			check_argv_exit(char **argv, t_list *l_free,
				int status, t_env content);
t_env		ft_cd(char **argv, t_env content);
t_env		ft_pwd(t_env content);
t_env		ft_env(char **argv, t_env content);
t_env		ft_export(char **argv, t_env content);
void		print_env(char **env);
t_env		ft_unset(char **argv, t_env content);
t_env		ft_echo(char **argv, t_env content);
int			check_ll(const char *str);

#endif
