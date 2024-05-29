/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:44:54 by jchauvet          #+#    #+#             */
/*   Updated: 2023/07/11 14:52:38 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <termios.h>
#include <unistd.h>

#include "signals.h"
#include "exec.h"
#include "global.h"

void	signal_ctlc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exec_exit_status_set(130);
	}
}

/* 			  close(STDIN_FILENO);				*/
/*		ft_putchar_fd('\n', STDERR_FILENO);		*/

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
		g_ctrl_c = 1;
}

/* FROM MAN PAGE: If ECHO is also set, terminal special */
/*			characters other than TAB, NL, START, and STOP are echoed */
/*			as ^X, where X is the character with ASCII code 0x40 */
/*			greater than the special character. */
/* WORKS LIKE I WANT IT TO BUT STILL KINDA BLACK MAGIC TO ME TOO */
/* WITHOUT THIS AFTER A WRONG INPUT, IT ECHOES ^/C WHEN YOU JUST  */
/* CTRL + C ON EMPTY INPUT, WHEN WE WANT NOTHING. */

int	termios_change(bool echo_ctl_chr)
{
	struct termios	terminos_p;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (ERROR);
	if (echo_ctl_chr)
		terminos_p.c_lflag |= ECHOCTL;
	else
		terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (ERROR);
	return (0);
}
