/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:03:16 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 11:11:33 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	is_numeric(char *s)
{
	if (!isdigit(*s))
		return (false);
	while (*s)
	{
		if (!isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}
bool	is_builtin(t_node_info *node)
{
	const char		*cmd_name;
	char			*builtin_commands[] = {"exit", "env", "export", "unset",
					"echo", "pwd", "cd"};
	unsigned int	i;

	if (node == NULL || node->cmd == NULL | node->cmd->node_token == NULL
		|| node->cmd->node_token->word == NULL)
		return (false);
	cmd_name = node->cmd->node_token->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	builtin_exit(t_prompt_info *info, char **argv)
{
	long	res;
	char	*arg;
	char	*endptr;

	if (argv[1] == NULL)
		exit(info->last_status);
	if (argv[2])
	{
		return (1);
	}
	arg = argv[1];
	if (is_numeric(arg))
	{
		errno = 0;
		res = strtol(arg, &endptr, 10);
		if (errno == 0 && *endptr == '\0')
			exit((int)res);
	}
	exit(255);
}

int	builtin_env(t_prompt_info *info)
{
	t_item	*item;

	item = info->map->item;
	while (item != NULL)
	{
		if (item->value)
			printf("%s=%s\n", item->name, item->value);
		item = item->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}

void	print_all_env(t_prompt_info *info)
{
	t_item	*item;

	item = info->map->item;
	while (item != NULL)
	{
		if (item->value)
		{
			printf("declare -x %s=\"%s\"\n", item->name, item->value);
		}
		else
		{
			printf("declare -x %s\n", item->name);
		}
		item = item->next;
	}
}

int	builtin_export(t_prompt_info *info, char **argv)
{
	size_t	i;
	int		status;

	if (argv[1] == NULL)
	{
		print_all_env(info);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		item_put(info, info->map, argv[i], 1);
		if (info->yourser_err == 1)
		{
			printf("error\n");
			status = 1;
		}
		i++;
	}
	return (status);
}

int	builtin_unset(t_prompt_info *info, char **argv)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (item_unset(info->map, argv[i]) < 0)
		{
			printf("error\n");
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	return (status);
}

int	builtin_echo(t_prompt_info *info, char **argv)
{
	size_t	i;
	int		new_line_flag;
	int		first_flag;

	(void)info;
	i = 1;
	new_line_flag = 1;
	if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		i++;
		new_line_flag = 0;
	}
	first_flag = 1;
	while (argv[i])
	{
		if (first_flag == 0)
			write(STDOUT_FILENO, " ", 1);
		first_flag = 0;
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
	}
	if (new_line_flag == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

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

void	exec_builtin(t_prompt_info *info, t_node_info *node)
{
	char	**cmd_argv;
	int		status;

	do_redirect(node);
	cmd_argv = token2argv(node->cmd->node_token);
	if (ft_strncmp(cmd_argv[0], "exit", 4) == 0)
	{
		status = builtin_exit(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strncmp(cmd_argv[0], "env", 3) == 0)
	{
		status = builtin_env(info);
		info->last_status = status;
	}
	else if (ft_strncmp(cmd_argv[0], "export", 6) == 0)
	{
		status = builtin_export(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strncmp(cmd_argv[0], "unset", 5) == 0)
	{
		status = builtin_unset(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strncmp(cmd_argv[0], "echo", 5) == 0)
	{
		status = builtin_echo(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strncmp(cmd_argv[0], "pwd", 3) == 0)
	{
		status = builtin_pwd(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strncmp(cmd_argv[0], "cd", 2) == 0)
	{
		status = builtin_cd(info, cmd_argv);
		info->last_status = status;
	}
	free(cmd_argv);
	reset_redirect(node);
	return ;
}
