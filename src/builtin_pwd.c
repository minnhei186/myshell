/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:38:34 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 13:32:27 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	equal_path(const char *path1, const char *path2)
{
	struct stat	pt1;
	struct stat	pt2;

	ft_memset(&pt1, 0, sizeof(pt1));
	ft_memset(&pt2, 0, sizeof(pt2));
	if (stat(path1, &pt1) < 0)
		printf("error\n");
	if (stat(path2, &pt2) < 0)
		printf("error\n");
	if (pt1.st_ino == pt2.st_ino)
		return (true);
	else
		return (false);
}

int	builtin_pwd(t_prompt_info *info, char **argv)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd = search_value(info->map->item, "PWD");
	if (pwd == NULL || !equal_path(pwd, "."))
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			printf("error\n");
			return (1);
		}
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
}
