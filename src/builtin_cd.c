/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:36:52 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 18:51:20 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	delete_last_path_element(char *path)
{
	int	i;
	int	last_slash_position;

	i = 0;
	last_slash_position = -1;
	while (path[i])
	{
		if (path[i] == '/')
			last_slash_position = i;
		i++;
	}
	if (last_slash_position == -1)
	{
		path[0] = '\0';
	}
	else if (last_slash_position == 0)
	{
		path[1] = '\0';
	}
	else
	{
		path[last_slash_position] = '\0';
	}
}

void	append_path_element(char *new_pwd, char **path_ppt, char *path)
{
	size_t	element_len;
	char	element[PATH_MAX];

	element_len = 0;
	while (path[element_len] && path[element_len] != '/')
		element_len++;
	if (new_pwd[ft_strlen(new_pwd) - 1] != '/')
		ft_strlcat(new_pwd, "/", PATH_MAX);
	ft_strlcpy(element, path, element_len + 1);
	ft_strlcat(new_pwd, element, PATH_MAX);
	*path_ppt = path + element_len;
}

char	*make_pwd(char *old_pwd, char *path)
{
	char	new_pwd[PATH_MAX];
	char	*dynamic_new_pwd;

	if (old_pwd == NULL)
		return (NULL);
	if (*path == '/')
		ft_strlcpy(new_pwd, "/", PATH_MAX);
	else
		ft_strlcpy(new_pwd, old_pwd, PATH_MAX);
	while (*path)
	{
		if ((*path) == '/')
			path++;
		else if (check_skip_path(&path, path, "."))
			;
		else if (check_skip_path(&path, path, ".."))
			delete_last_path_element(new_pwd);
		else
			append_path_element(new_pwd, &path, path);
	}
	dynamic_new_pwd = minishell_strdup(new_pwd);
	return (dynamic_new_pwd);
}

void	copy_home_value(t_prompt_info *info, char *path)
{
	char	*home;

	home = item_value_get(info->map, "HOME");
	if (home == NULL)
	{
		free(home);
		minishell_yourser_perror(info, "fild to get home value");
		return ;
	}
	ft_strlcpy(path, home, PATH_MAX);
	free(home);
}

int	builtin_cd(t_prompt_info *info, char **argv)
{
	char	path[PATH_MAX];
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = item_value_get(info->map, "PWD");
	item_set(info->map, "OLDPWD", old_pwd);
	if (argv[1] == NULL)
	{
		copy_home_value(info, path);
		if (info->yourser_err == 1)
			return (1);
	}
	else
		ft_strlcpy(path, argv[1], PATH_MAX);
	if (chdir(path) < 0)
	{
		minishell_yourser_perror(info, "faild to chdir");
		free(old_pwd);
		return (1);
	}
	new_pwd = make_pwd(old_pwd, path);
	item_set(info->map, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
