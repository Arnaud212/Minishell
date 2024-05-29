/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:41:40 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/23 18:19:24 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**env_unset_var(char *name, char **env)
{
	char	*env_var;

	env_var = env_find_var(name, env);
	if (env_var == NULL)
		return (env);
	env = split_remove_str(&env, env_var);
	return (env);
}

char	**env_put_var(char *str, char **env)
{
	char	*old_var;
	char	*new_var;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return (env);
	new_var = ft_strdup(str);
	if (new_var == NULL)
	{
		print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
		return (env);
	}
	old_var = env_find_var(str, env);
	env = split_replace_str(&env, old_var, new_var);
	if (old_var == NULL)
	{
		env = split_append_str(&env, new_var);
		if (env == NULL)
		{
			print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
			return (env);
		}
	}
	return (env);
}

char	**env_set_env(char *name, char *value, char **env)
{
	char	*var_str;
	char	*tmp;

	if (name == NULL || value == NULL)
		return (env);
	tmp = ft_strjoin(name, "=");
	if (tmp == NULL)
	{
		print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
		return (env);
	}
	var_str = ft_strjoin(tmp, value);
	free(tmp);
	if (var_str == NULL)
	{
		print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
		return (env);
	}
	env = env_put_var(var_str, env);
	free(var_str);
	return (env);
}
