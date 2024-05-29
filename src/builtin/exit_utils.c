/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:23:31 by agiraud           #+#    #+#             */
/*   Updated: 2023/07/11 15:23:40 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_long_long(const char *str, int is_negative, size_t str_len)
{
	const char	*comparison_str;
	size_t		i;

	if (is_negative)
		comparison_str = "9223372036854775808";
	else
		comparison_str = "9223372036854775807";
	i = 0;
	if (str_len > 19)
		return (1);
	else if (str_len < 19)
		return (0);
	else
	{
		while (i < str_len)
		{
			if (str[i] > comparison_str[i])
				return (1);
			else if (str[i] < comparison_str[i])
				return (0);
			i++;
		}
	}
	return (0);
}

int	check_ll(const char *str)
{
	size_t	str_len;
	int		is_negative;

	str_len = 0;
	is_negative = 0;
	if (str[0] == '-')
	{
		is_negative = 1;
		str++;
	}
	while (str[str_len] != '\0')
		str_len++;
	return (check_long_long(str, is_negative, str_len));
}
