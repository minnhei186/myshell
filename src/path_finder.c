/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:05:38 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/12 14:17:49 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

char	*cut_and_move_env(char **path_env)
{
	int		len;
	char	*tail_p;
	char	*unit_path;

	tail_p = ft_strchr(*path_env, ':');
	if (tail_p == NULL)
		return (NULL);
	len = tail_p - (*path_env);
	unit_path = (char *)malloc(sizeof(char) * len + 1);
	strncpy(unit_path, (*path_env), len);
	unit_path[len] = '\0';
	*path_env = *path_env + len + 1;
	return (unit_path);
}

char	*make_command_path(char *command, char *unit_path)
{
	char	*path_slash;
	char	*command_path;

	path_slash = ft_strjoin(unit_path, "/");
	command_path = ft_strjoin(path_slash, command);
	free(path_slash);
	return (command_path);
}
char	*path_get(t_prompt_info *info,char *command)
{
	char	*path_env;
	char	*unit_path;
	char	*command_path;

	if (strchr(command, '/') != NULL && access(command, F_OK) == 0)
		return command;
	path_env=item_value_get(info->map,"PATH");
	if(path_env==NULL)
		return NULL;
	while (1)
	{
		unit_path = cut_and_move_env(&path_env);
		if (unit_path == NULL)
			return (NULL);
		command_path = make_command_path(command, unit_path);
		free(unit_path);
		if (access(command_path, F_OK) == 0)
			return (command_path);
	}
	return (NULL);
}
