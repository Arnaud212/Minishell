/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:53:45 by agiraud           #+#    #+#             */
/*   Updated: 2023/06/23 17:58:46 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	ft_unset(char **argv, t_env content)
{
	int	i;

	i = 1;
	content.status = 0;
	while (argv[i])
	{
		if (!env_find_var(argv[i], content.env))
			;
		else
			content.env = env_unset_var(argv[i], content.env);
		i++;
	}
	return (content);
}
