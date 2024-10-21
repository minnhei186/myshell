/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:03:16 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/21 15:39:50 by hosokawa         ###   ########.fr       */
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
		if (ft_strcmp(cmd_name, builtin_commands[i])==0)
			return (true);
		i++;
	}
	return (false);
}

void	exec_builtin(t_prompt_info *info, t_node_info *node)
{
	char	**cmd_argv;
	int		status;

	do_redirect(node->cmd->redirects);
	cmd_argv = token2argv(node->cmd->node_token);
	if (ft_strcmp(cmd_argv[0], "exit") == 0)
	{
		status = builtin_exit(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strcmp(cmd_argv[0], "env") == 0)
	{
		status = builtin_env(info);
		info->last_status = status;
	}
	else if (ft_strcmp(cmd_argv[0], "export") == 0)
	{
		status = builtin_export(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strcmp(cmd_argv[0], "unset") == 0)
	{
		status = builtin_unset(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strcmp(cmd_argv[0], "echo") == 0)
	{
		status = builtin_echo(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strcmp(cmd_argv[0], "pwd") == 0)
	{
		status = builtin_pwd(info, cmd_argv);
		info->last_status = status;
	}
	else if (ft_strcmp(cmd_argv[0], "cd") == 0)
	{
		status = builtin_cd(info, cmd_argv);
		info->last_status = status;
	}
	ppt_free(cmd_argv);
	do_reset_redirect(node->cmd->redirects);
	return ;
}
