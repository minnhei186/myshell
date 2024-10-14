/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:36:52 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 11:15:49 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"


bool check_skip_path(char **path_ppt,char *path,char *check_str)
{
	size_t check_str_len;

	check_str_len=ft_strlen(check_str);

	if(ft_strncmp(path,check_str,check_str_len)==0)
	{
		if(path[check_str_len]=='\0'||path[check_str_len]=='/')
		{
			*path_ppt=path+check_str_len;
			return true;
		}
	}
	return false;
	
}


void delete_last_path_element(char *path)
{
	int i;
	int last_slash_position;
	

	i=0;
	while(path[i])
	{
		if(path[i]=='/')
			last_slash_position=i;
		i++;
	}
	if(last_slash_position==0)
	{
		while(path[last_slash_position])
		{
				path[last_slash_position]='\0';
				last_slash_position++;
		}
	}
}


void append_path_element(char *new_pwd,char **path_ppt,char *path)
{
	size_t element_len;

	element_len=0;
	while(path[element_len]&&path[element_len]!='/')
		element_len++;
	if(new_pwd[ft_strlen(new_pwd)-1]!='/')
		ft_strlcat(new_pwd,"/",PATH_MAX);
	*path_ppt=path+element_len;
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
			append_path_element(new_pwd,&path,path);
	}
	dynamic_new_pwd = ft_strdup(new_pwd);
	return (dynamic_new_pwd);
}

int	builtin_cd(t_prompt_info *info, char **argv)
{
	char	path[PATH_MAX];
	char	*old_pwd;
	char	*home;
	char *new_pwd;

	old_pwd = item_value_get(info->map, "PWD");
	item_set(info->map, "OLDPWD", old_pwd);
	if (argv[1] == NULL)
	{
		home = item_value_get(info->map, "HOME");
		if (home == NULL)
		{
			printf("error\n");
			return (1);
		}
		ft_strlcpy(path, home, PATH_MAX);
	}
	else
	{
		ft_strlcpy(path, argv[1], PATH_MAX);
	}
	if (chdir(path) < 0)
	{
		printf("error\n");
		return 1;
	}
	new_pwd = make_pwd(old_pwd, path);
	item_set(info->map, "PWD", new_pwd);
	free(old_pwd);
	return (0);
}
