/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:38:46 by jchauvet          #+#    #+#             */
/*   Updated: 2023/08/16 08:41:30 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

#include "global.h"

int	test_sig(char *read_str, int mode)
{
	if (read_str && mode == 1)
		free(read_str);
	if (g_ctrl_c == 1)
		return (1);
	return (0);
}

char	*free_and_print(char *here_str)
{
	free(here_str);
	print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM));
	return (NULL);
}
