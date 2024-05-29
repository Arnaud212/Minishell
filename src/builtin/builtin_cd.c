/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:33:14 by agiraud           #+#    #+#             */
/*   Updated: 2023/08/02 16:26:42 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <sys/stat.h>

char	*add_home_path(char *path, t_env content)
{
	char		*tmp;
	char		*tmpp;

	tmp = env_get_value("HOME", content.env);
	if (tmp)
	{
		tmpp = ft_substr(path, 1, ft_strlen(path));
		path = ft_strjoin(tmp, tmpp);
		free(tmpp);
		return (path);
	}
	return (path);
}

t_env	change(char *path, t_env content)
{
	char	*pwd;
	char	*new_pwd;

	content.i = 0;
	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			content.env = env_set_env("OLDPWD", pwd, content.env);
			free(pwd);
		}
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			content.env = env_set_env("PWD", new_pwd, content.env);
			free(new_pwd);
		}
		content.i = 1;
		return (content);
	}
	free(pwd);
	return (content);
}

t_env	set_directory(char *path, t_env content)
{
	struct stat	st;

	content = change(path, content);
	if (content.i == 1)
		return (content);
	if (stat(path, &st) == -1)
	{
		print_error(SHELL_NAME, "cd", path, "No such file or directory");
		content.status = 1;
		return (content);
	}
	else if (!(st.st_mode & S_IXUSR))
	{
		print_error(SHELL_NAME, "cd", path, "Permission denied");
		content.status = 1;
		return (content);
	}
	else
	{
		print_error(SHELL_NAME, "cd", path, "Not a directory");
		content.status = 1;
		return (content);
	}
	return (content);
}

t_env	ft_tilde(char *home, t_env content)
{
	if (!home)
	{
		print_error(SHELL_NAME, "cd", NULL, "HOME not set");
		content.status = 1;
		return (content);
	}
	return (set_directory(home, content));
}

t_env	ft_cd(char **args, t_env content)
{
	char	*home;
	char	*rel;

	content.status = 0;
	rel = NULL;
	home = env_get_value("HOME", content.env);
	if (args && args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		content.status = 1;
		return (content);
	}
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		return (ft_tilde(home, content));
	}
	if (ft_strncmp(args[1], "~/", 2) == 0)
	{
		rel = add_home_path(args[1], content);
		content = set_directory(rel, content);
		free(rel);
		return (content);
	}
	return (set_directory(args[1], content));
}
