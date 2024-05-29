/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:10:32 by agiraud           #+#    #+#             */
/*   Updated: 2023/06/23 18:15:21 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	ft_env(char **argv, t_env content)
{
	int	i;

	i = 0;
	if (!argv[1])
	{
		if (content.env && content.env[i])
		{
			while (content.env[i])
			{
				printf("%s\n", content.env[i]);
				i++;
			}
		}
	}
	else
	{
		print_error(SHELL_NAME, argv[0], NULL, "Too many arguments");
		content.status = -1;
		return (content);
	}
	return (content);
}
