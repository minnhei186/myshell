/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:36:52 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/08 17:26:03 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "myshell.h"
//
//
//bool	consume_path(char **rest, char *path, char *elm)
//{
//	size_t	elm_len;
//
//	elm_len = strlen(elm);
//	if (strncmp(path, elm, elm_len) == 0)
//	{
//		if (path[elm_len] == '\0' || path[elm_len] == '/')
//		{
//			*rest = path + elm_len;
//			return (true);
//		}
//	}
//	return (false);
//}
//
//void	delete_last_elm(char *path)
//{
//	char	*start;
//	char	*last_slash_ptr;
//
//	start = path;
//	last_slash_ptr = NULL;
//	while (*path)
//	{
//		if (*path == '/')
//			last_slash_ptr = path;
//		path++;
//	}
//	if (last_slash_ptr != start)
//		*last_slash_ptr = '\0';
//}
//
//void	append_path_elm(char *dst, char **rest, char *src)
//{
//	size_t	elm_len;
//
//	elm_len = 0;
//	while (src[elm_len] && src[elm_len] != '/')
//		elm_len++;
//	// TODO: strcat, strncat is unsafe
//	if (dst[strlen(dst) - 1] != '/')
//		strcat(dst, "/");
//	strncat(dst, src, elm_len);
//	*rest = src + elm_len;
//}
//
//char	*resolve_pwd(char *oldpwd, char *path)
//{
//	char	newpwd[PATH_MAX];
//	char	*dup;
//
//	if (*path == '/' || oldpwd == NULL)
//		strlcpy(newpwd, "/", PATH_MAX);
//	else
//		strlcpy(newpwd, oldpwd, PATH_MAX);
//	while (*path)
//	{
//		if (*path == '/')
//			path++;
//		else if (consume_path(&path, path, "."))
//			;
//		else if (consume_path(&path, path, ".."))
//			delete_last_elm(newpwd);
//		else
//			append_path_elm(newpwd, &path, path);
//	}
//	dup = strdup(newpwd);
//	if (dup == NULL)
//		fatal_error("strdup");
//	return (dup);
//}
//
//void	builtin_cd(char **envmap,char **argv)
//{
//	char	*home;
//	char	*oldpwd;
//	char	path[PATH_MAX];
//	char	*newpwd;
//
//	oldpwd = map_get(envmap, "PWD");
//	map_set(envmap, "OLDPWD", oldpwd);
//	if (argv[1] == NULL)
//	{
//		home = map_get(envmap, "HOME");
//		if (home == NULL)
//		{
//			builtin_error("cd", NULL, "HOME not set");
//			return (1);
//		}
//		strlcpy(path, home, PATH_MAX);
//	}
//	else
//		strlcpy(path, argv[1], PATH_MAX);
//	if (chdir(path) < 0)
//	{
//		builtin_error("cd", NULL, "chdir");
//		return (1);
//	}
//	newpwd = resolve_pwd(oldpwd, path);
//	map_set(envmap, "PWD", newpwd);
//	free(newpwd);
//	return (0);
//}
