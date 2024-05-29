/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:39:17 by jchauvet          #+#    #+#             */
/*   Updated: 2023/06/23 18:04:31 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "global.h"

char	**env_init(char **env);
char	*env_get_value(char *name, char **env);
char	*env_find_var(char *name, char **env);
bool	env_var_is_value(char *var_name, char *value, char **env);
bool	env_is_var_char(char c);
char	**env_unset_var(char *name, char **env);
char	**env_put_var(char *str, char **env);
char	**env_set_env(char *name, char *value, char **env);

#endif
