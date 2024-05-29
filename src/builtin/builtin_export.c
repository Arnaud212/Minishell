/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:50:02 by agiraud           #+#    #+#             */
/*   Updated: 2023/08/15 11:53:02 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*ft_export_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	name = ft_substr(str, 0, i);
	return (name);
}

char	*ft_export_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (ft_strdup(""));
	value = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	return (value);
}

t_env	ft_print_env_if_no_args(char **argv, t_env content)
{
	if (!argv[1])
	{
		print_env(content.env);
		return (content);
	}
	return (content);
}

t_env	ft_set_env_vars(char **argv, t_env content)
{
	int		i;
	char	*ex_name;
	char	*ex_val;

	i = 1;
	while (argv[i])
	{
		if (!ft_isalpha(argv[i][0]) && argv[i][0] != '_')
		{
			print_error(SHELL_NAME, "export", argv[i],
				"not a valid identifier");
			content.status = 1;
		}
		else
		{
			ex_name = ft_export_name(argv[i]);
			ex_val = ft_export_value(argv[i]);
			content.env = env_set_env(ex_name, ex_val, content.env);
			free(ex_name);
			free(ex_val);
		}
		i++;
	}
	return (content);
}

t_env	ft_export(char **argv, t_env content)
{
	content = ft_print_env_if_no_args(argv, content);
	content = ft_set_env_vars(argv, content);
	return (content);
}
