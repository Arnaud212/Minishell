/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:05:24 by agiraud           #+#    #+#             */
/*   Updated: 2023/06/21 19:12:18 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	**sort_env(char **tmp_env)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	len = 0;
	i = 0;
	while (tmp_env[len])
		len++;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (strcmp(tmp_env[i], tmp_env[j]) > 0)
			{
				temp = tmp_env[i];
				tmp_env[i] = tmp_env[j];
				tmp_env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (tmp_env);
}

char	*ft_copy_and_quote(char *new_env, char *env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (env[i])
	{
		new_env[j] = env[i];
		if (env[i] == '=' && k == 0)
		{
			j++;
			new_env[j] = '"';
			k++;
		}
		j++;
		i++;
	}
	new_env[j] = '"';
	new_env[j + 1] = '\0';
	return (new_env);
}

char	**copy_env(char **env)
{
	int		len;
	int		i;
	char	**new_env;

	len = 0;
	while (env[len])
		len++;
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 3));
		if (!new_env[i])
		{
			ft_free_split(&new_env);
			return (NULL);
		}
		new_env[i] = ft_copy_and_quote(new_env[i], env[i]);
		i++;
	}
	new_env[len] = NULL;
	return (new_env);
}

void	print_env(char **env)
{
	char	**tmp_env;
	int		i;

	i = 0;
	tmp_env = copy_env(env);
	tmp_env = sort_env(tmp_env);
	while (tmp_env[i])
	{
		printf("declare -x %s\n", tmp_env[i]);
		i++;
	}
	ft_free_split(&tmp_env);
}
