/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:07:08 by agiraud           #+#    #+#             */
/*   Updated: 2023/07/05 20:13:07 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**env_allocate(int size)
{
	char	**env;

	env = malloc((size + 1) * sizeof(char *));
	if (env == NULL)
	{
		print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
		return (NULL);
	}
	return (env);
}

char	**env_copy(char **source, char **target)
{
	int	i;

	i = 0;
	while (source[i])
	{
		target[i] = ft_strdup(source[i]);
		if (target[i] == NULL)
		{
			ft_free_split(&target);
			print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
			return (NULL);
		}
		i++;
	}
	target[i] = NULL;
	return (target);
}

char	**env_init(char **env)
{
	extern char	**environ;
	int			i;

	i = split_count(environ);
	if (i == 0)
		return (0);
	env = env_allocate(i);
	if (env == NULL)
		return (NULL);
	env = env_copy(environ, env);
	return (env);
}
