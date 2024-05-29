/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:39:41 by jchauvet          #+#    #+#             */
/*   Updated: 2023/08/16 08:45:01 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>

# include "libft.h"

# define ERROR		-1

# define PROMPT 	"$> "
# define SHELL_NAME	"minishell"
# define DEBUG_ENV	"DEBUG"

typedef struct s_env_content
{
	int		status;
	int		i;
	char	**env;
}	t_env;

extern int	g_ctrl_c;

int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);
char	*minishell_get_next_line(int fd);
int		lst_node_remove(t_list **lst, t_list *node, void (*del)(void *));
t_list	*lst_node_prev(t_list *lst, t_list *node);
int		lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end);
int		split_count(char **argv);
char	**split_append_str(char ***split, char *str);
char	**split_remove_str(char ***split, char *remove_str);
char	**split_replace_str(char ***split, char *old_str, char *new_str);
void	split_sort(char **split);
char	*str_append_str(char *str, char *append);
char	*str_append_chr(char *str, char append);
char	str_last_chr(char *str);
int		test_sig(char *read_str, int mode);
char	*free_and_print(char *here_str);

#endif
