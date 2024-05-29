/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:03:27 by agiraud           #+#    #+#             */
/*   Updated: 2023/07/11 15:25:30 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	number_of_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_is_num(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_argv_exit(char **argv, t_list *l_free, int status, t_env content)
{
	if (argv[0] && !argv[1])
	{
		exec_free_all(argv, l_free, content);
		exit(status);
	}
	if (!ft_is_num(argv[1]) || argv[1][0] == '\0')
	{
		print_error(SHELL_NAME, "exit", argv[1], "numeric argument required");
		exec_free_all(argv, l_free, content);
		exit(2);
	}
	if (number_of_argv(argv) > 2)
	{
		print_error(SHELL_NAME, "exit", NULL, "too many arguments");
		return (1);
	}
	return (0);
}

t_env	ft_exit(char **argv, int status, t_list *l_free, t_env content)
{
	content.status = 0;
	if (isatty(STDERR_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (check_argv_exit(argv, l_free, status, content))
	{
		content.status = 1;
		return (content);
	}
	if (check_ll(argv[1]))
	{
		print_error(SHELL_NAME, "exit", argv[1], "numeric argument required");
		exec_free_all(argv, l_free, content);
		exit(2);
	}
	status = ft_atoi(argv[1]);
	exec_free_all(argv, l_free, content);
	exit(status);
	return (content);
}
