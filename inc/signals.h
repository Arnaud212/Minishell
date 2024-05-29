/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:40:11 by jchauvet          #+#    #+#             */
/*   Updated: 2023/02/09 10:03:02 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "global.h"

void	signal_ctlc(int sig);
void	signal_ctlc_heredoc(int sig);
int		termios_change(bool echo_ctl_chr);

#endif
