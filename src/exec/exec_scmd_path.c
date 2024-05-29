/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:41:55 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/21 16:53:57 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "exec.h"
#include "env.h"

static int	path_find(char **path_split, char **argv);
static char	**path_split_get(t_env content);
static int	path_split_append_slash(char **path_split);

int	exec_scmd_search_path(char **argv, t_env content)
{
	char	**path_split;

	path_split = NULL;
	if (env_get_value("PATH", content.env) && argv[0][0] != '\0')
	{
		path_split = path_split_get(content);
		if (path_split == NULL)
			return (ERROR);
		if (path_find(path_split, argv) == 0)
		{
			ft_free_split(&path_split);
			return (0);
		}
	}
	if (path_split)
		ft_free_split(&path_split);
	return (ERROR);
}

static int	path_find(char **path_split, char **argv)
{
	struct stat	s;
	char		*tmp;
	int			i;

	i = 0;
	while (path_split && path_split[i])
	{
		tmp = ft_strjoin(path_split[i], *argv);
		if (tmp == NULL)
		{
			print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
			return (ERROR);
		}
		if (access(tmp, F_OK) == 0 && (!stat(tmp, &s) && !S_ISDIR(s.st_mode)))
		{
			free(*argv);
			*argv = tmp;
			return (0);
		}
		free(tmp);
		i++;
	}
	return (ERROR);
}

static char	**path_split_get(t_env content)
{
	char	**path_split;

	path_split = NULL;
	if (env_get_value("PATH", content.env))
	{
		path_split = ft_split(env_get_value("PATH", content.env), ':');
		if (path_split == NULL)
		{
			print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
			return (NULL);
		}
	}
	if (path_split_append_slash(path_split) == ERROR)
	{
		ft_free_split(&path_split);
		return (NULL);
	}
	return (path_split);
}

static int	path_split_append_slash(char **path_split)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path_split && path_split[i])
	{
		if (path_split[i][ft_strlen(path_split[i]) - 1] != '/')
		{
			tmp = path_split[i];
			path_split[i] = ft_strjoin(path_split[i], "/");
			if (path_split[i] == NULL)
			{
				path_split[i] = tmp;
				return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
			}
			free(tmp);
		}
		i++;
	}
	return (0);
}
