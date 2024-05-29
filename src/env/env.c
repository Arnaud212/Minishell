/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:41:48 by jchauvet          #+#    #+#             */
/*   Updated: 2023/07/05 20:11:14 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*env_get_value(char *name, char **env)
{
	char	*env_var;

	env_var = env_find_var(name, env);
	if (env_var)
		return (ft_strchr(env_var, '=') + 1);
	else
		return (NULL);
}

char	*env_find_var(char *name, char **env)
{
	int	l_name;
	int	i;

	if (name == NULL || env == NULL)
		return (NULL);
	if (ft_strchr(name, '='))
		l_name = ft_strchr(name, '=') - name;
	else
		l_name = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], l_name) && env[i][l_name] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

bool	env_var_is_value(char *var_name, char *value, char **env)
{
	char	*env_value;

	env_value = env_get_value(var_name, env);
	if (env_value)
		if (ft_strncmp(env_value, value, ft_strlen(value) + 1) == 0)
			return (true);
	return (false);
}

bool	env_is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
