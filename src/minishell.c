/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:45:47 by jchauvet          #+#    #+#             */
/*   Updated: 2023/08/15 10:42:49 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "global.h"
#include "env.h"
#include "exec.h"
#include "lexer.h"
#include "parser.h"
#include "signals.h"

static char		*get_input(t_env content);
static t_env	process_input(char *input, t_env content);
static void		close_all(void);

int	g_ctrl_c = 0;

t_env	st_init(void)
{
	t_env	content;

	content.env = NULL;
	content.env = env_init(content.env);
	content.status = 0;
	return (content);
}

int	main(void)
{
	char	*input;
	t_env	content;

	signal(SIGQUIT, SIG_IGN);
	content = st_init();
	if (content.env == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, signal_ctlc);
		termios_change(false);
		input = get_input(content);
		if (input == NULL)
		{
			if (isatty(STDERR_FILENO))
				ft_putendl_fd("exit", STDERR_FILENO);
			termios_change(true);
			break ;
		}
		content = process_input(input, content);
	}
	close_all();
	if (content.env)
		ft_free_split(&content.env);
	exit(exec_exit_status_get());
}

static char	*get_input(t_env content)
{
	char	*input;
	char	*prompt;

	prompt = env_get_value("PS1", content.env);
	if (prompt == NULL)
		prompt = PROMPT;
	if (isatty(STDIN_FILENO))
		input = readline(prompt);
	else
		input = minishell_get_next_line(STDIN_FILENO);
	if (input == NULL)
		return (NULL);
	else if (isatty(STDIN_FILENO) && input && input[0])
		add_history(input);
	return (input);
}

static t_env	process_input(char *input, t_env content)
{
	t_list	*l_token;
	t_list	*l_parser;

	signal(SIGINT, SIG_IGN);
	errno = 0;
	l_token = NULL;
	l_parser = NULL;
	l_token = lexer(input, content);
	free(input);
	if (l_token != NULL)
		l_parser = parser(l_token, content);
	if (l_token != NULL && l_parser != NULL)
		content = exec_recursive(l_parser, l_parser, content);
	if (l_parser != NULL)
		ft_lstclear(&l_parser, c_cmd_destroy);
	else if (l_token != NULL)
		ft_lstclear(&l_token, c_token_destroy);
	return (content);
}

static void	close_all(void)
{
	struct stat	buf;

	rl_clear_history();
	if (fstat(STDIN_FILENO, &buf) != -1)
		close(STDIN_FILENO);
	if (fstat(STDOUT_FILENO, &buf) != -1)
		close(STDOUT_FILENO);
	if (fstat(STDERR_FILENO, &buf) != -1)
		close(STDERR_FILENO);
}
