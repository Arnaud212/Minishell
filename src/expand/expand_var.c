/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:36:37 by jchauvet          #+#    #+#             */
/*   Updated: 2023/07/11 14:33:48 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "env.h"
#include "exec.h"

static int	expand_var_token(t_c_token *c_token, t_env content);
static int	expanded_str_get(t_c_token *c_token, char **exp_str,
				int *i, t_env content);
static int	expanded_str_append_exit_code(char **exp_str);
static int	expanded_str_append_var(char **exp_str, char *str, t_env content);

int	expand_var_token_list(t_list *l_token, t_env content)
{
	t_list	*iter;

	iter = l_token;
	while (iter)
	{
		if (expand_var_token(token_content(iter), content) == ERROR)
			return (ERROR);
		iter = iter->next;
	}
	return (0);
}

static int	expand_var_token(t_c_token *c_token, t_env content)
{
	char	*exp_str;
	int		i;

	if (c_token->str == NULL || (c_token->flags & TOK_S_QUOTE)
		|| !ft_strchr(c_token->str, '$')
		|| (c_token->flags & TOK_REDIR_FILE && c_token->flags & TOK_D_QUOTE))
		return (0);
	exp_str = ft_strdup("");
	if (exp_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	i = 0;
	while (c_token->str[i])
	{
		while (c_token->str[i] == '$' && c_token->str[i + 1] == '$')
			i++;
		if (expanded_str_get(c_token, &exp_str, &i, content) == ERROR)
		{
			free(exp_str);
			return (ERROR);
		}
		i++;
	}
	free(c_token->str);
	c_token->str = exp_str;
	return (0);
}

static int	expanded_str_get(t_c_token *c_token, char **exp_str,
				int *i, t_env c)
{
	if (c_token->str[*i] == '$' && c_token->str[*i + 1] == '?')
	{
		if (expanded_str_append_exit_code(exp_str) == ERROR)
			return (ERROR);
		(*i)++;
	}
	else if (check_token(c_token, i))
	{
		if (expanded_str_append_var(exp_str, &(c_token->str[*i]), c) == ERROR)
			return (ERROR);
		while (env_is_var_char(c_token->str[*i + 1]))
		{
			if (c_token->str[*i] == '$' && ft_isdigit(c_token->str[*i + 1]))
			{
				(*i)++;
				break ;
			}
			(*i)++;
		}
	}
	else
		*exp_str = str_append_chr(*exp_str, c_token->str[*i]);
	if (*exp_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

static int	expanded_str_append_exit_code(char **exp_str)
{
	char	*exit_str;

	exit_str = ft_itoa(exec_exit_status_get());
	if (exit_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	*exp_str = str_append_str(*exp_str, exit_str);
	free(exit_str);
	if (*exp_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

static int	expanded_str_append_var(char **exp_str, char *var, t_env content)
{
	char	*var_name;
	char	*var_value;
	int		i;

	var_name = ft_strdup("");
	if (var_name == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	i = 1;
	while (env_is_var_char(var[i]))
	{
		var_name = str_append_chr(var_name, var[i]);
		if (var_name == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		if (ft_isdigit(var[1]))
			break ;
		i++;
	}
	var_value = env_get_value(var_name, content.env);
	free(var_name);
	if (var_value == NULL)
		var_value = "";
	*exp_str = str_append_str(*exp_str, var_value);
	if (*exp_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}
