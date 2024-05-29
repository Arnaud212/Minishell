/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:45:34 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/23 18:00:51 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

char	**split_append_str(char ***split, char *new_str)
{
	char	**new_split;
	int		i;

	new_split = malloc((split_count(*split) + 2) * sizeof(char *));
	if (new_split == NULL)
		return (NULL);
	i = 0;
	while (*split && (*split)[i])
	{
		new_split[i] = (*split)[i];
		i++;
	}
	new_split[i] = new_str;
	new_split[i + 1] = NULL;
	free(*split);
	*split = new_split;
	return (*split);
}

char	**split_remove_str(char ***split, char *remove_str)
{
	char	**new_split;
	int		i;

	new_split = malloc(split_count(*split) * sizeof(char *));
	if (new_split == NULL)
		return (NULL);
	i = 0;
	while ((*split)[i] != remove_str)
	{
		new_split[i] = (*split)[i];
		i++;
	}
	free(remove_str);
	while ((*split)[i + 1])
	{
		new_split[i] = (*split)[i + 1];
		i++;
	}
	new_split[i] = NULL;
	free(*split);
	*split = new_split;
	return (*split);
}

char	**split_replace_str(char ***split, char *old_str, char *new_str)
{
	int	i;

	if (*split == NULL || old_str == NULL)
		return (*split);
	i = 0;
	while ((*split)[i] && (*split)[i] != old_str)
		i++;
	if ((*split)[i] != old_str)
		return (*split);
	free(old_str);
	(*split)[i] = new_str;
	return (*split);
}

void	split_sort(char **split)
{
	char	*tmp;
	int		i_strs;
	int		i;
	int		j;

	i_strs = split_count(split);
	i = 0;
	while (i < i_strs - 1)
	{
		j = 0;
		while (j < (i_strs - 1 - i))
		{
			if (ft_strncmp(split[j], split[j + 1], ft_strlen(split[j]) + 1) > 0)
			{
				tmp = split[j];
				split[j] = split[j + 1];
				split[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
