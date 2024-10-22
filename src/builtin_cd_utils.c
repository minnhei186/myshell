/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:18:43 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 13:19:02 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	check_skip_path(char **path_ppt, char *path, char *check_str)
{
	size_t	check_str_len;

	check_str_len = ft_strlen(check_str);
	if (ft_strncmp(path, check_str, check_str_len) == 0)
	{
		if (path[check_str_len] == '\0' || path[check_str_len] == '/')
		{
			*path_ppt = path + check_str_len;
			return (true);
		}
	}
	return (false);
}
