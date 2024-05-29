/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:42:09 by agiraud           #+#    #+#             */
/*   Updated: 2023/06/21 20:19:14 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <sys/stat.h>

t_env	ft_pwd(t_env content)
{
	char	*dir;

	content.status = 0;
	dir = env_get_value("PWD", content.env);
	if (!dir)
	{
		perror("minishell: pwd: error");
		content.status = -1;
		return (content);
	}
	printf("%s\n", dir);
	return (content);
}
